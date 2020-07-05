#include "PrecompiledHeader.h"

#include <array>

#include "Misc/Windows/SafeFileHandle.h"
#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../File.h"

namespace tg
{
namespace
{

#if !defined(S_ISREG)
constexpr bool S_ISREG(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFREG;
}
#endif

std::optional<struct _stat> CreateStat(const char8_t* path, const std::span<wchar_t>& utf16PathBuffer)
{
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16PathBuffer[0], static_cast<int>(utf16PathBuffer.size())) == 0)
    {
        return {};
    }

    struct _stat s{};
    if (_wstat(&utf16PathBuffer[0], &s) != 0)
    {
        return {};
    }

    return s;
}

}

bool File::Copy(const char8_t* srcPath, const char8_t* destPath, bool overwrite)
{
    auto utf16SrcPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&srcPath[0]), static_cast<int32_t>(std::char_traits<char8_t>::length(srcPath) + 1));
    auto utf16DestPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&destPath[0]), static_cast<int32_t>(std::char_traits<char8_t>::length(destPath) + 1));

    return CopyFileW(reinterpret_cast<LPCWSTR>(utf16SrcPath.data()), reinterpret_cast<LPCWSTR>(utf16DestPath.data()), overwrite ? FALSE : TRUE) != 0;
}

bool File::Delete(const char8_t* path)
{
    std::array<wchar_t, 4096> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    return _wremove(&utf16Path[0]) == 0;
}

bool File::Exists(const char8_t* path)
{
    std::array<wchar_t, 4096> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    return true;
}

bool File::Move(const char8_t* srcPath, const char8_t* destPath)
{
    std::array<wchar_t, 4096> utf16SrcPath{};
    auto s = CreateStat(srcPath, utf16SrcPath);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    std::array<wchar_t, 4096> utf16DestPath{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(destPath), -1, &utf16DestPath[0], static_cast<int>(std::extent_v<decltype(utf16DestPath)>)) == 0)
    {
        return {};
    }

    return _wrename(&utf16SrcPath[0], &utf16DestPath[0]) == 0;
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const char8_t* path)
{
    std::array<wchar_t, 4096> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_atime);
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const char8_t* path)
{
    std::array<wchar_t, 4096> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_mtime);
}

bool File::SetCreationTimeUtc(const char8_t* path, const DateTime& creationTimeUtc)
{
    std::array<wchar_t, 4096> utf16Path{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16Path[0], static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    const SafeFileHandle handle = CreateFile2(&utf16Path[0], GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (handle.IsValid() == false)
    {
        return false;
    }

    const int64_t ticks = creationTimeUtc.ToFileTimeUtc();
    FILETIME fileTime = {
        .dwLowDateTime = static_cast<DWORD>(ticks),
        .dwHighDateTime = static_cast<DWORD>(ticks >> 32)
    };
    if (SetFileTime(handle, &fileTime, nullptr, nullptr) == 0)
    {
        return false;
    }

    return true;
}

bool File::SetLastAccessTimeUtc(const char8_t* path, const DateTime& lastAccessTimeUtc)
{
    std::array<wchar_t, 4096> utf16Path{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16Path[0], static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    const SafeFileHandle handle = CreateFile2(&utf16Path[0], GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (handle.IsValid() == false)
    {
        return false;
    }

    const int64_t ticks = lastAccessTimeUtc.ToFileTimeUtc();
    FILETIME fileTime{static_cast<DWORD>(ticks), static_cast<DWORD>(ticks >> 32)};
    if (SetFileTime(handle, nullptr, &fileTime, nullptr) == 0)
    {
        return false;
    }

    return true;
}

bool File::SetLastWriteTimeUtc(const char8_t* path, const DateTime& lastWriteTimeUtc)
{
    wchar_t utf16Path[4096];
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, utf16Path, static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    SafeFileHandle handle = CreateFile2(utf16Path, GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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

std::optional<DateTime> File::GetCreationTimeUtc(const char8_t* path)
{
    wchar_t utf16Path[4096];
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_ctime);
}

std::optional<FileAttributes> File::GetAttributes(const char8_t* path)
{
    wchar_t utf16Path[4096];
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, utf16Path, static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
    if (GetFileAttributesExW(reinterpret_cast<LPCWSTR>(utf16Path), GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &fileAttributeData) == FALSE)
    {
        return {};
    }

    return FileAttributes(fileAttributeData.dwFileAttributes);
}

bool File::Decrypt(const char8_t* path)
{
    wchar_t utf16Path[4096];
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, utf16Path, static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    return DecryptFileW(utf16Path, 0) == TRUE;
}

bool File::Encrypt(const char8_t* path)
{
    wchar_t utf16Path[4096];
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, utf16Path, static_cast<int>(std::extent_v<decltype(utf16Path)>)) == 0)
    {
        return {};
    }

    return EncryptFileW(utf16Path) == TRUE;
}

}
