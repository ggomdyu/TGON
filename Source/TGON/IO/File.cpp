#include "PrecompiledHeader.h"

#include <cstdio>
#include <sys/stat.h>

#include "Time/TimeZoneInfo.h"

#include "File.h"

namespace tgon
{

bool File::Copy(const std::string_view& srcFileName, const std::string_view& destFileName) noexcept
{
    return Copy(srcFileName, destFileName, false);
}

bool File::Copy(const std::string_view& srcFileName, const std::string_view& destFileName, bool overwrite) noexcept
{
    return true;
}

bool File::Delete(const char* path)
{
    return remove(path) == 0;
}

bool File::Exists(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return false;
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool File::Move(const char* srcFileName, const char* destFileName)
{
    return std::rename(srcFileName, destFileName) == 0;
}

std::optional<DateTime> File::GetCreationTime(const char* path)
{
    auto ret = GetCreationTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}
    
std::optional<DateTime> File::GetCreationTimeUtc(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return {};
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }
    
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_birthtimespec.tv_sec);
}


std::optional<DateTime> File::GetLastAccessTime(const char* path)
{
    auto ret = GetLastAccessTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return {};
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }
    
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atimespec.tv_sec);
}

} /* namespace tgon */
