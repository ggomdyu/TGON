#include "PrecompiledHeader.h"

#include <sys/stat.h>

#include "../File.h"

namespace tgon
{

bool File::Delete(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return remove(path) == 0;
}

bool File::Exists(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool File::Move(const char* srcPath, const char* destPath)
{
    struct stat s;
    if (stat(srcPath, &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return rename(srcPath, destPath) == 0;
}

std::optional<DateTime> File::GetCreationTimeUtc(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return {};
    }

#if TGON_PLATFORM_MACOS
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_birthtimespec.tv_sec);
#else
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_ctime);
#endif
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return {};
    }

#if TGON_PLATFORM_MACOS
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atimespec.tv_sec);
#else
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atime);
#endif
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const char* path)
{
    struct stat s;
    if (stat(path, &s) != 0)
    {
        return {};
    }

#if TGON_PLATFORM_MACOS
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_mtimespec.tv_sec);
#else
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_mtime);
#endif
}

} /* namespace tgon */
