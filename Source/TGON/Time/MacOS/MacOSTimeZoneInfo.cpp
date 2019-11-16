#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>

#include "../TimeZoneInfo.h"

namespace tgon
{
namespace
{

TimeZoneInfo CreateLocal()
{
    NSTimeZone* localTimeZone = [NSTimeZone localTimeZone];
    NSLocale* currentLocale = [NSLocale currentLocale];
    
    const char* id = [localTimeZone name].UTF8String;
    const char* standardName = [localTimeZone localizedName:NSTimeZoneNameStyleStandard locale:currentLocale].UTF8String;
    const char* daylightDisplayName = [localTimeZone localizedName:NSTimeZoneNameStyleDaylightSaving locale:currentLocale].UTF8String;
    TimeSpan baseUtcOffset(TimeSpan::TicksPerSecond * [localTimeZone secondsFromGMT]);
    bool supportsDaylightSavingTime = [localTimeZone isDaylightSavingTime];
    
    return TimeZoneInfo(id, baseUtcOffset, standardName, standardName, daylightDisplayName, supportsDaylightSavingTime);
}
    
} /* namespace */

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = CreateLocal();
    return timeZoneInfo;
}

} /* namespace tgon */
