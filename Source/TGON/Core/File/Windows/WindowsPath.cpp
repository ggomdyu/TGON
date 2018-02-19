#include "PrecompiledHeader.pch"

#include "../Path.h"

#include "Core/String/Encoding.h"

#include <Windows.h>
#include <shlobj.h>

namespace tgon
{
namespace core
{

TGON_API std::string GetCurrentDirectoryPath()
{
    wchar_t utf16Path[MAX_PATH + 1] {};
    DWORD utf16PathLen = GetCurrentDirectoryW(MAX_PATH + 1, utf16Path);

    char utf8Path[MAX_PATH + 1] {};
    UTF16LE::Convert<UTF8>((const char*)utf16Path, utf16PathLen, &utf8Path[0], sizeof(utf8Path));

    return utf8Path;
}

TGON_API std::string GetUserDirectoryPath()
{
    wchar_t utf16Path[MAX_PATH + 1];

    if (SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, utf16Path) == S_OK)
    {
        char utf8Path[MAX_PATH]{};
        UTF16LE::Convert<UTF8>((const char*)utf16Path, std::wcslen(utf16Path), &utf8Path[0], sizeof(utf8Path));

        return utf8Path;
    }
    else
    {
        return std::string();
    }
}

TGON_API std::string GetDesktopDirectoryPath()
{
    wchar_t utf16Path[MAX_PATH + 1];

    if (SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, 0, utf16Path) == S_OK)
    {
        char utf8Path[MAX_PATH] {};
        UTF16LE::Convert<UTF8>((const char*)utf16Path, std::wcslen(utf16Path), &utf8Path[0], sizeof(utf8Path));

        return utf8Path;
    }
    else
    {
        return std::string();
    }
}

} /* namespace core */
} /* namespace tgon */
