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

bool File::SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc)
{
    std::u16string utf16Path = UTF8::ConvertTo<UTF16LE>(path);

    SafeFileHandle handle = CreateFile2(reinterpret_cast<LPCWSTR>(utf16Path.c_str()), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
    if (static_cast<HANDLE>(handle) == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    auto ticks = lastWriteTimeUtc.ToFileTimeUtc().GetTicks();
    FILETIME fileTime = *reinterpret_cast<const FILETIME*>(&ticks);
    auto c = SetFileTime(handle, nullptr, nullptr, &fileTime);

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