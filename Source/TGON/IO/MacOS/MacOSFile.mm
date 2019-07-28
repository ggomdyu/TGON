#import "PrecompiledHeader.h"

#import <cstdio>
#import <sys/stat.h>

#import "../File.h"

namespace tgon
{

std::optional<DateTime> File::GetCreationTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0)
    {
        return {};
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }
   
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_birthtimespec.tv_sec);
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0)
    {
        return {};
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atime.tv_sec);
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0)
    {
        return {};
    }

    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_mtimespec.tv_sec);
}

} /* namespace tgon */
