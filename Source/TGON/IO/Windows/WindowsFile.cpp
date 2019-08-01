#include "PrecompiledHeader.h"

#include <Windows.h>

#include "String/Encoding.h"
#include "Misc/Windows/SafeFileHandle.h"

#include "../File.h"

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#   define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

namespace tgon
{

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
    struct stat s;
    if (stat(path.data(), &s) != 0)
    {
        return {};
    }
    
    if (S_ISREG(s.st_mode) == false)
    {
        return {};
    }
   
    return DateTime(DateTime::GetUnixEpoch().GetTicks() + TimeSpan::TicksPerSecond * s.st_ctime);
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

} /* namespace tgon */