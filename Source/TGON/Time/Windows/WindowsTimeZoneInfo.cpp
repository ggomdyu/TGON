#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"

#include "../TimeZoneInfo.h"

namespace tgon
{
namespace
{

TimeZoneInfo CreateLocal()
{
    DYNAMIC_TIME_ZONE_INFORMATION tzi;
    bool isSupportDaylightSavingTime = GetDynamicTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN;

    char id[std::extent_v<decltype(tzi.TimeZoneKeyName)> * sizeof(tzi.TimeZoneKeyName[0])];
    char standardName[std::extent_v<decltype(tzi.StandardName)> * sizeof(tzi.StandardName[0])];
    char daylightDisplayName[std::extent_v<decltype(tzi.DaylightName)> * sizeof(tzi.DaylightName[0])];

    int32_t idBytes = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.TimeZoneKeyName), id);
    int32_t standardNameBytes = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.StandardName), standardName);
    int32_t daylightDisplayNameBytes = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.DaylightName), daylightDisplayName);
    
    TimeSpan baseUtcOffset(TimeSpan::TicksPerMinute * -tzi.Bias);

    return TimeZoneInfo(std::string(id, idBytes), baseUtcOffset, std::string(standardName, standardNameBytes), std::string(standardName, standardNameBytes), std::string(daylightDisplayName, daylightDisplayNameBytes), isSupportDaylightSavingTime);
}
    
}

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = CreateLocal();
    return timeZoneInfo;
}

}
