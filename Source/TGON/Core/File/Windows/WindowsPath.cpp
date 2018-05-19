#include "PrecompiledHeader.h"

#include <Windows.h>
#include <shlobj.h>

#include "Core/String/Encoding.h"

#include "../Path.h"

#ifdef GetCurrentDirectory
#   undef GetCurrentDirectory
#endif

namespace tgon
{

TGON_API std::string GetCurrentDirectory()
{
    wchar_t utf16Path[MAX_PATH] {};
    DWORD utf16PathLen = GetCurrentDirectoryW(MAX_PATH, utf16Path);

    char utf8Path[MAX_PATH + 1] {};
    UTF16LE::Convert<UTF8>((const char*)utf16Path, utf16PathLen, &utf8Path[0], sizeof(utf8Path));

    return utf8Path;
}

TGON_API std::string GetUserDirectory()
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

TGON_API std::string GetDesktopDirectory()
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

} /* namespace tgon */