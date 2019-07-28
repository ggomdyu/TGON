#import "PrecompiledHeader.h"

#import <Foundation/Foundation.h>

#import "../TimeZoneInfo.h"

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

//std::vector<std::string> GetTimeZoneNames()
//{
//    NSArray* array = [NSTimeZone knownTimeZoneNames];
//
//    std::vector<std::string> ret;
//    ret.reserve(array.count);
//
//    for (int i = 0; i < array.count; ++i)
//    {
//        NSString* timeZoneName = [array[i] name];
//        ret.push_back([timeZoneName UTF8String]);
//    }
//
//    return ret;
//}

//TimeZoneInfo TimeZoneInfo::CreateTimeZoneInfo(const std::string_view& timeZoneName)
//{
//    NSString* timeZoneName2 = [[NSString alloc] initWithUTF8String: timeZoneName];
//    
//    NSTimeZone* timeZone = [[NSTimeZone alloc] initWithName: nsTimeZoneName2];
//    
//}

} /* namespace tgon */
