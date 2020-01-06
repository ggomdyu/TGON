#include "PrecompiledHeader.h"

#include <array>

#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../TimeZoneInfo.h"

namespace tgon
{

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = []()
    {
        DYNAMIC_TIME_ZONE_INFORMATION tzi;
        bool isSupportDaylightSavingTime = GetDynamicTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN;
        
        TimeSpan baseUtcOffset(TimeSpan::TicksPerMinute * -tzi.Bias);

        std::array<char, 512> utf8Id;
        auto utf8IdBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.TimeZoneKeyName), static_cast<int32_t>(wcslen(tzi.TimeZoneKeyName) * 2), reinterpret_cast<std::byte*>(&utf8Id[0]), static_cast<int32_t>(utf8Id.size()));
        std::array<char, 128> utf8StandardName;
        auto utf8StandardNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.StandardName), static_cast<int32_t>(wcslen(tzi.StandardName) * 2), reinterpret_cast<std::byte*>(&utf8StandardName[0]), static_cast<int32_t>(utf8StandardName.size()));
        std::array<char, 128> utf8DaylightDisplayName;
        auto utf8DaylightDisplayNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(tzi.DaylightName), static_cast<int32_t>(wcslen(tzi.DaylightName) * 2), reinterpret_cast<std::byte*>(&utf8DaylightDisplayName[0]), static_cast<int32_t>(utf8DaylightDisplayName.size()));

        return TimeZoneInfo(std::string(&utf8Id[0], utf8IdBytes), baseUtcOffset, std::string(&utf8StandardName[0], utf8StandardNameBytes), std::string(&utf8StandardName[0], utf8StandardNameBytes), std::string(&utf8DaylightDisplayName[0], utf8DaylightDisplayNameBytes), isSupportDaylightSavingTime);
    } ();
    return timeZoneInfo;
}

} /* namespace tgon */