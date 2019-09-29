#include "PrecompiledHeader.h"

#include <Windows.h>
#include <array>

#include "String/Encoding.h"
#include "Misc/Windows/SafeFileHandle.h"

#include "../File.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

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

    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return {};
    }

    if (_wstat(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()), &s) != 0)
    {
        return {};
    }

    return s;
}

} /* namespace */

bool File::Copy(const std::string_view& srcPath, const std::string_view& destPath, bool overwrite) noexcept
{
    auto utf16SrcPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&srcPath[0]), srcPath.size() + 1);
    auto utf16DestPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&destPath[0]), destPath.size() + 1);

    return CopyFileW(reinterpret_cast<LPCWSTR>(utf16SrcPath.data()), reinterpret_cast<LPCWSTR>(utf16DestPath.data()), overwrite ? FALSE : TRUE) != 0;
}

bool File::Delete(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return _wremove(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data())) == 0;
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
    const wchar_t* utf16SrcPath = &g_tempUtf16Buffer[0];
    auto utf16SrcPathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(srcPath.data()), static_cast<int32_t>(srcPath.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16SrcPathBytes == -1)
    {
        return false;
    }

    auto utf16PathLen = utf16SrcPathBytes / 2;
    wchar_t* utf16DestPath = &g_tempUtf16Buffer[utf16PathLen + 1];
    auto utf16DestPathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(destPath.data()), static_cast<int32_t>(destPath.size()), reinterpret_cast<std::byte*>(utf16DestPath), static_cast<int32_t>(g_tempUtf16Buffer.size() - (utf16SrcPathBytes + 2)));
    if (utf16DestPathBytes == -1)
    {
        return false;
    }

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath), reinterpret_cast<const wchar_t*>(utf16DestPath)) == 0;
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
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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

std::optional<FileAttributes> File::GetAttributes(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return {};
    }

    WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
    if (GetFileAttributesExW(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data()), GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &fileAttributeData) == FALSE)
    {
        return {};
    }

    return FileAttributes(fileAttributeData.dwFileAttributes);
}

bool File::Decrypt(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return DecryptFileW(g_tempUtf16Buffer.data(), 0) == TRUE;
}

bool File::Encrypt(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return EncryptFileW(g_tempUtf16Buffer.data()) == TRUE;
}

std::string File::ReadAllText(const std::string_view& path)
{
    return ReadAllText(path, Encoding::UTF8());
}

std::string File::ReadAllText(const std::string_view& path, const Encoding& encoding)
{
    return std::string(nullptr);
}

FileStream File::Create(const std::string_view& path)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Create(const std::string_view& path, int32_t bufferSize)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize);
}

FileStream File::Create(const std::string_view& path, int32_t bufferSize, FileOptions options)
{
    return FileStream(path, FileMode::Create, FileAccess::ReadWrite, FileShare::None, bufferSize, options);
}

FileStream File::Open(const std::string_view& path, FileMode mode)
{
    return Open(path, mode, mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite, FileShare::None);
}

FileStream File::Open(const std::string_view& path, FileMode mode, FileAccess access)
{
    return Open(path, mode, access, FileShare::None);
}

FileStream File::Open(const std::string_view& path, FileMode mode, FileAccess access, FileShare share)
{
    return FileStream(path, mode, access, share);
}

} /* namespace tgon */
