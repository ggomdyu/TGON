#include "PrecompiledHeader.h"

#include <cstdio>
#include <array>
#include <sys/stat.h>

#include "Time/TimeZoneInfo.h"

#include "File.h"

namespace tgon
{
namespace
{
    
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
constexpr bool S_ISREG(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFREG;
}
#endif
    
} /* namespace */

bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath)
{
    return Copy(srcPath, destPath, false);
}

#if TGON_PLATFORM_WINDOWS == 0
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

#if TGON_PLATFORM_MACOS == 0
std::optional<DateTime> File::GetLastAccessTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_atime);
}
#endif

#if TGON_PLATFORM_MACOS == 0
std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view& path)
{
    struct stat s;
    if (stat(path.data(), &s) != 0 || S_ISREG(s.st_mode) == false)
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

std::optional<std::vector<std::byte>> File::ReadAllBytes(const std::string_view& path)
{
    FileStream fs(path.data(), FileMode::Open, FileAccess::Read, FileShare::Read);
    if (fs.IsClosed() || fs.Length() > INT_MAX)
    {
        return {};
    }

    int32_t fileBytes = static_cast<int32_t>(fs.Length());
    int32_t index = 0;

    std::vector<std::byte> ret(static_cast<size_t>(fileBytes));
    while (fileBytes > 0)
    {
        auto readBytes = fs.Read(&ret[index], 4096);

        index += readBytes;
        fileBytes -= readBytes;
    }

    return ret;
}

} /* namespace tgon */
