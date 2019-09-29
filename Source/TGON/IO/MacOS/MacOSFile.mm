#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>
#include <sys/stat.h>
#include <utime.h>
#include <cstdio>

#include "../File.h"

namespace tgon
{
namespace
{
    
NSDate* ConvertDateTimeToNative(const DateTime& dateTime)
{
    NSDateComponents* dateComponents = [[NSDateComponents alloc] init];
    [dateComponents setYear:dateTime.GetYear()];
    [dateComponents setMonth:dateTime.GetMonth()];
    [dateComponents setDay:dateTime.GetDay()];
    [dateComponents setHour:dateTime.GetHour()];
    [dateComponents setMinute:dateTime.GetMinute()];
    [dateComponents setSecond:dateTime.GetSecond()];
    
    NSCalendar* calendar = [NSCalendar currentCalendar];
    
    NSDate* modificationDate = [[calendar dateFromComponents:dateComponents] dateByAddingTimeInterval:[[NSTimeZone systemTimeZone] secondsFromGMT]];
    return modificationDate;
}
    
} /* namespace */
    
bool File::SetCreationTimeUtc(const std::string_view& path, const DateTime& creationTimeUtc)
{
    NSDate* date = ConvertDateTimeToNative(creationTimeUtc);
    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: date, NSFileCreationDate, nullptr];
    
    NSFileManager* fileManager = [NSFileManager defaultManager];
    bool isSucceed = [fileManager setAttributes: attributes ofItemAtPath: [NSString stringWithUTF8String:path.data()] error: nullptr];
    return isSucceed;
}
    
bool File::SetLastAccessTimeUtc(const std::string_view& path, const DateTime& lastAccessTimeUtc)
{
    int64_t ticks = (lastAccessTimeUtc.ToUniversalTime().GetTicks() - DateTime::GetUnixEpoch().GetTicks()) / TimeSpan::TicksPerSecond;
    
    utimbuf buf{ticks, ticks};
    return utime(path.data(), &buf) == 0;
}

bool File::SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc)
{
    NSDate* dateComponents = ConvertDateTimeToNative(lastWriteTimeUtc);
    
    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: dateComponents, NSFileModificationDate, nullptr];
    return [[NSFileManager defaultManager] setAttributes:attributes ofItemAtPath:[NSString stringWithUTF8String:path.data()] error:nil];
}

std::optional<DateTime> File::GetCreationTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }
   
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_birthtimespec.tv_sec);
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }
    
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atimespec.tv_sec);
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_mtimespec.tv_sec);
}

bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath, bool overwrite)
{
    if (overwrite)
    {
        Delete(destPath);
    }
    
    NSString* nsSrcPath = [NSString stringWithUTF8String:srcPath.data()];
    NSString* nsDestPath = [NSString stringWithUTF8String:destPath.data()];
    return [[NSFileManager defaultManager] copyItemAtPath:nsSrcPath toPath:nsDestPath error:nil];
}

} /* namespace tgon */
