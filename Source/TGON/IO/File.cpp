#include "PrecompiledHeader.h"

#include <cstdio>
#include <sys/stat.h>

#include "String/Encoding.h"
#include "Time/TimeZoneInfo.h"

#include "File.h"

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#   define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

namespace tgon
{

bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath) noexcept
{
    return Copy(srcPath, destPath, false);
}

#if TGON_PLATFORM_FILESYSTEM_UTF16 == 0
bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath, bool overwrite) noexcept
{
    Delete(srcPath);

    return true;
}

bool File::Delete(const std::string_view& path)
{
    return remove(path.data()) == 0;
}

bool File::Exists(const std::string_view& path)
{
    struct stat s;

    if (stat(path.data(), &s) != 0)
    {
        return false;
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return false;
    }
    
    return true;
}

bool File::Move(const std::string_view& srcPath, const std::string_view& destPath)
{
    return std::rename(srcPath.data(), destPath.data()) == 0;
}

#if TGON_PLATFORM_MACOS == 0
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

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atime);
}
#endif

#if TGON_PLATFORM_MACOS == 0
std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view & path)
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

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_mtime);
}
#endif
#endif

std::optional<DateTime> File::GetCreationTime(const std::string_view& path)
{
    auto ret = GetCreationTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}

std::optional<DateTime> File::GetLastAccessTime(const std::string_view& path)
{
    auto ret = GetLastAccessTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
}

std::optional<DateTime> File::GetLastWriteTime(const std::string_view& path)
{
    auto ret = GetLastWriteTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }

    return ret;
}

bool File::SetCreationTime(const std::string_view& path, const DateTime& creationTime)
{
    return SetCreationTimeUtc(path, creationTime);
}

bool File::SetLastAccessTime(const std::string_view& path, const DateTime& lastAccessTime)
{
    return SetLastAccessTimeUtc(path, lastAccessTime);
}

bool File::SetLastWriteTime(const std::string_view& path, const DateTime& lastWriteTime)
{
    return SetLastWriteTimeUtc(path, lastWriteTime);
}

} /* namespace tgon */
