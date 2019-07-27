#include "PrecompiledHeader.h"

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


    char rawId[std::extent_v<decltype(tzi.TimeZoneKeyName)> * sizeof(tzi.TimeZoneKeyName[0])];
    int32_t idLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.TimeZoneKeyName), rawId);
    
    char standardName[std::extent_v<decltype(tzi.StandardName)> * sizeof(tzi.StandardName[0])];
    int32_t standardNameLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.StandardName), standardName);
    
    char daylightDisplayName[std::extent_v<decltype(tzi.DaylightName)> * sizeof(tzi.DaylightName[0])];
    int32_t daylightDisplayNameLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(tzi.DaylightName), daylightDisplayName);
    
    TimeSpan baseUtcOffset(TimeSpan::TicksPerMinute * -tzi.Bias);

    return TimeZoneInfo(std::string(rawId, idLen), baseUtcOffset, std::string(standardName, standardNameLen), std::string(standardName, standardNameLen), std::string(daylightDisplayName, daylightDisplayNameLen), isSupportDaylightSavingTime);
}
    
} /* namespace */

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = CreateLocal();
    return timeZoneInfo;
}

} /* namespace tgon */
