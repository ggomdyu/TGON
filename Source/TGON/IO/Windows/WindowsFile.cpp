#include "PrecompiledHeader.h"

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

    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);
    if (_wstat(reinterpret_cast<const wchar_t*>(utf16Path.data()), &s) != 0)
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

    return CopyFileW(reinterpret_cast<LPCWSTR>(utf16SrcPath.data()), reinterpret_cast<LPCWSTR>(utf16DestPath.data()), !overwrite) != 0;
}

bool File::Delete(const std::string_view& path)
{
    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);

    return _wremove(reinterpret_cast<LPCWSTR>(utf16Path.data())) == 0;
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
    auto utf16SrcPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&srcPath[0]), srcPath.size() + 1);
    auto utf16DestPath = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&destPath[0]), destPath.size() + 1);

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
    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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
    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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
    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.data()), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
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
    auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&path[0]), path.size() + 1);

    WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
    if (GetFileAttributesExW(reinterpret_cast<LPCWSTR>(utf16Path.data()), GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &fileAttributeData) == FALSE)
    {
        return FileAttributes();
    }

    return FileAttributes(fileAttributeData.dwFileAttributes);
}

} /* namespace tgon */
