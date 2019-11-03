#include "PrecompiledHeader.h"

#include <array>

#include "Text/Encoding.h"
#include "Misc/Windows/SafeFileHandle.h"
#include "Platform/Windows/Windows.h"

#include "../File.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

namespace
{

#if !defined(S_ISREG)
constexpr bool S_ISREG(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFREG;
}
#endif

std::optional<struct _stat> CreateStat(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return {};
    }

    struct _stat s;
    if (_wstat(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()), &s) != 0)
    {
        return {};
    }

    return s;
}

} /* namespace */

bool File::Copy(const char* srcPath, const char* destPath, bool overwrite)
{
    auto utf16SrcPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&srcPath[0]), static_cast<int32_t>(strlen(srcPath) + 1));
    auto utf16DestPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&destPath[0]), static_cast<int32_t>(strlen(destPath) + 1));

    return CopyFileW(reinterpret_cast<LPCWSTR>(utf16SrcPath.data()), reinterpret_cast<LPCWSTR>(utf16DestPath.data()), overwrite ? FALSE : TRUE) != 0;
}

bool File::Delete(const char* path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    return _wremove(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data())) == 0;
}

bool File::Exists(const char* path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    return true;
}

bool File::Move(const char* srcPath, const char* destPath)
{
    auto s = CreateStat(srcPath);
    if (s.has_value() == false || S_ISREG(s->st_mode) == false)
    {
        return false;
    }

    wchar_t* utf16SrcPath = &g_tempUtf16Buffer[0];
    auto utf16SrcPathLen = wcslen(utf16SrcPath);

    wchar_t* utf16DestPath = &g_tempUtf16Buffer[utf16SrcPathLen + 1];
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(destPath), static_cast<int32_t>(strlen(destPath)), reinterpret_cast<std::byte*>(utf16DestPath), static_cast<int32_t>(g_tempUtf16Buffer.size() - (utf16SrcPathLen + 1))) == -1)
    {
        return false;
    }

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath), reinterpret_cast<const wchar_t*>(utf16DestPath)) == 0;
}

std::optional<DateTime> File::GetLastAccessTimeUtc(const char* path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_atime);
}

std::optional<DateTime> File::GetLastWriteTimeUtc(const char* path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_mtime);
}

bool File::SetCreationTimeUtc(const char* path, const DateTime& creationTimeUtc)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    // TODO: Support directory
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

bool File::SetLastAccessTimeUtc(const char* path, const DateTime& lastAccessTimeUtc)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    // TODO: Support directory
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

bool File::SetLastWriteTimeUtc(const char* path, const DateTime& lastWriteTimeUtc)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    // TODO: Support directory
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

std::optional<DateTime> File::GetCreationTimeUtc(const char* path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false)
    {
        return {};
    }

    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s->st_ctime);
}

std::optional<FileAttributes> File::GetAttributes(const char* path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
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

bool File::Decrypt(const char* path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return DecryptFileW(g_tempUtf16Buffer.data(), 0) == TRUE;
}

bool File::Encrypt(const char* path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return EncryptFileW(g_tempUtf16Buffer.data()) == TRUE;
}

std::string File::ReadAllText(const char* path, const Encoding& encoding)
{
    // TODO: Implement
    return std::string(nullptr);
}

} /* namespace tgon */
