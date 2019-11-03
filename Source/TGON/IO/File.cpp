#include "PrecompiledHeader.h"

#include <cstdio>
#include <array>
#include <sys/stat.h>

#include "Time/TimeZoneInfo.h"

#include "File.h"

namespace tgon
{

std::optional<DateTime> File::GetCreationTime(const char* path)
{
    auto ret = GetCreationTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }
    
    return ret;
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

std::optional<DateTime> File::GetLastWriteTime(const char* path)
{
    auto ret = GetLastWriteTimeUtc(path);
    if (ret)
    {
        return ret.value() + TimeZoneInfo::Local().GetBaseUtcOffset();
    }

    return ret;
}

bool File::SetCreationTime(const char* path, const DateTime& creationTime)
{
    return SetCreationTimeUtc(path, creationTime);
}

bool File::SetLastAccessTime(const char* path, const DateTime& lastAccessTime)
{
    return SetLastAccessTimeUtc(path, lastAccessTime);
}

bool File::SetLastWriteTime(const char* path, const DateTime& lastWriteTime)
{
    return SetLastWriteTimeUtc(path, lastWriteTime);
}

std::optional<std::vector<std::byte>> File::ReadAllBytes(const char* path)
{
    FileStream fs(path, FileMode::Open, FileAccess::Read, FileShare::Read);
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

std::string File::ReadAllText(const char* path)
{
    return ReadAllText(path, Encoding::UTF8());
}

FileStream File::Create(const char* path)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Create(const char* path, int32_t bufferSize)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize);
}

FileStream File::Create(const char* path, int32_t bufferSize, FileOptions options)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize, options);
}

FileStream File::Open(const char* path, FileMode mode)
{
    return Open(path, mode, mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Open(const char* path, FileMode mode, FileAccess access)
{
    return Open(path, mode, access, FileShare::None);
}

FileStream File::Open(const char* path, FileMode mode, FileAccess access, FileShare share)
{
    return FileStream(path, mode, access, share);
}

} /* namespace tgon */
