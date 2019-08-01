#import "PrecompiledHeader.h"

#import <utime.h>
#import <cstdio>
#import <sys/stat.h>

#import "../File.h"

namespace tgon
{
    
bool File::SetLastAccessTimeUtc(const std::string_view& path, const DateTime& lastAccessTime)
{
    return false;
}

bool File::SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc)
{
    int64_t ticks = (lastWriteTimeUtc.ToUniversalTime().GetTicks() - DateTime::GetUnixEpoch().GetTicks()) / TimeSpan::TicksPerSecond;
    
    utimbuf buf{0, ticks};
    return utime(path.data(), &buf) == 0;
}

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

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atimespec.tv_sec);
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
