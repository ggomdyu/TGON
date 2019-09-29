#include "PrecompiledHeader.h"

#include <sys/stat.h>

#include "File.h"

namespace tgon
{

bool File::Delete(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return remove(path.data()) == 0;
}

bool File::Exists(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool File::Move(const std::string_view& srcPath, const std::string_view& destPath)
{
    return std::rename(srcPath.data(), destPath.data()) == 0;
}

std::optional<DateTime> File::GetCreationTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }

#if TGON_PLATFORM_MACOS
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_birthtimespec.tv_sec);
#else
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_ctime);
#endif
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }

#if TGON_PLATFORM_MACOS
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atimespec.tv_sec);
#else
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atime);
#endif
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
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
