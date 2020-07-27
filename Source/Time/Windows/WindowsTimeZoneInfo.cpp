#include "PrecompiledHeader.h"

#include <array>

#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../TimeZoneInfo.h"

namespace tg
{

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = []()
    {
        DYNAMIC_TIME_ZONE_INFORMATION tzi;
        const bool isSupportDaylightSavingTime = GetDynamicTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN;
        
        const TimeSpan baseUtcOffset(TimeSpan::TicksPerMinute * -tzi.Bias);

        std::array<char, 512> utf8Id{};
        const auto utf8IdByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.TimeZoneKeyName), static_cast<int32_t>(std::char_traits<wchar_t>::length(tzi.TimeZoneKeyName) * 2), reinterpret_cast<std::byte*>(&utf8Id[0]), static_cast<int32_t>(utf8Id.size()));

        std::array<char, 128> utf8StandardName{};
        const auto utf8StandardNameByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.StandardName), static_cast<int32_t>(std::char_traits<wchar_t>::length(tzi.StandardName) * 2), reinterpret_cast<std::byte*>(&utf8StandardName[0]), static_cast<int32_t>(utf8StandardName.size()));

        std::array<char, 128> utf8DaylightDisplayName{};
        const auto utf8DaylightDisplayNameByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.DaylightName), static_cast<int32_t>(std::char_traits<wchar_t>::length(tzi.DaylightName) * 2), reinterpret_cast<std::byte*>(&utf8DaylightDisplayName[0]), static_cast<int32_t>(utf8DaylightDisplayName.size()));

        return TimeZoneInfo(std::string(&utf8Id[0], utf8IdByteCount), baseUtcOffset, std::string(&utf8StandardName[0], utf8StandardNameByteCount), std::string(&utf8StandardName[0], utf8StandardNameByteCount), std::string(&utf8DaylightDisplayName[0], utf8DaylightDisplayNameByteCount), isSupportDaylightSavingTime);
    } ();
    return timeZoneInfo;
}

}