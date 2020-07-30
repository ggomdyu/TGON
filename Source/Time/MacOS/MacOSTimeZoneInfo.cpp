#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>

#include "../TimeZoneInfo.h"

namespace tg
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
    const TimeSpan baseUtcOffset(TimeSpan::TicksPerSecond * [localTimeZone secondsFromGMT]);
    const bool supportsDaylightSavingTime = [localTimeZone isDaylightSavingTime];
    
    return TimeZoneInfo(id, baseUtcOffset, standardName, standardName, daylightDisplayName, supportsDaylightSavingTime);
}
    
}

const TimeZoneInfo& TimeZoneInfo::Local()
{
    static auto timeZoneInfo = CreateLocal();
    return timeZoneInfo;
}

}
