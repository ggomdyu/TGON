#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"
#include "Misc/Windows/SafeFileHandle.h"

#include "../File.h"

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

std::optional<struct _stat> CreateStat(const std::string_view& path)
{
    struct _stat s;

    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);
    if (_wstat(reinterpret_cast<const wchar_t*>(utf16Path.data()), &s) != 0)
    {
        return {};
    }

    return s;
}

}

bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath, bool overwrite) noexcept
{
    std::u16string utf16SrcPath = UTF8::ConvertTo<UTF16LE>(srcPath);
    std::u16string utf16DestPath = UTF8::ConvertTo<UTF16LE>(destPath);

    return CopyFileW(reinterpret_cast<LPCWSTR>(utf16SrcPath.c_str()), reinterpret_cast<LPCWSTR>(utf16DestPath.c_str()), !overwrite) != 0;
}

bool File::Delete(const std::string_view& path)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    return _wremove(reinterpret_cast<LPCWSTR>(utf16Path.c_str())) == 0;
}

bool File::Exists(const std::string_view& path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    return true;
}

bool File::Move(const std::string_view& srcPath, const std::string_view& destPath)
{
    std::u16string utf16SrcPath = UTF8::ConvertTo<UTF16LE>(srcPath);
    std::u16string utf16DestPath = UTF8::ConvertTo<UTF16LE>(destPath);

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath.data()), reinterpret_cast<const wchar_t*>(utf16DestPath.data())) == 0;
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const std::string_view& path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_atime);
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const std::string_view& path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_mtime);
}

bool File::SetCreationTimeUtc(const std::string_view& path, const DateTime& creationTimeUtc)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.c_str()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (handle.IsValid() == false)
    {
        return false;
    }

    int64_t ticks = creationTimeUtc.ToFileTimeUtc();
    FILETIME fileTime{static_cast<DWORD>(ticks), static_cast<DWORD>(ticks >> 32)};
    if (SetFileTime(handle, &fileTime, nullptr, nullptr) == 0)
    {
        return false;
    }

    return true;
}

bool File::SetLastAccessTimeUtc(const std::string_view& path, const DateTime& lastAccessTimeUtc)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.c_str()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (handle.IsValid() == false)
    {
        return false;
    }

    int64_t ticks = lastAccessTimeUtc.ToFileTimeUtc();
    FILETIME fileTime{static_cast<DWORD>(ticks), static_cast<DWORD>(ticks >> 32)};
    if (SetFileTime(handle, nullptr, &fileTime, nullptr) == 0)
    {
        return false;
    }

    return true;
}

bool File::SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.c_str()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (handle.IsValid() == false)
    {
        return false;
    }

    int64_t ticks = lastWriteTimeUtc.ToFileTimeUtc();
    FILETIME fileTime{static_cast<DWORD>(ticks), static_cast<DWORD>(ticks >> 32)};
    if (SetFileTime(handle, nullptr, nullptr, &fileTime) == 0)
    {
        return false;
    }

    return true;
}

std::optional<DateTime> File::GetCreationTimeUtc(const std::string_view& path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_ctime);
}

FileAttributes File::GetAttributes(const std::string_view& path)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
    if (GetFileAttributesExW(reinterpret_cast<LPCWSTR>(utf16Path.c_str()), GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &fileAttributeData) == FALSE)
    {
        return FileAttributes();
    }

    return FileAttributes(fileAttributeData.dwFileAttributes);
}

}