#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>
#include <shlobj.h>

#include "String/Encoding.h"

#include "../Path.h"

namespace tgon
{

TGON_API int32_t Path::GetCurrentDirectory(char* destStr)
{
    wchar_t utf16Path[MAX_PATH + 1] {};
    DWORD utf16PathLen = GetCurrentDirectoryW(MAX_PATH, utf16Path);

    bool isConvertSucceed = UTF16LE::ConvertTo<UTF8>(std::wstring_view(utf16Path, utf16PathLen), destStr, MAX_PATH) != -1;
    if (isConvertSucceed)
    {
        return utf16PathLen;
    }
    else
    {
        return -1;
    }
}

TGON_API int32_t GetSpecialDirectory(int csidl, char* destStr)
{
    wchar_t utf16Path[MAX_PATH + 1];

    if (SHGetFolderPathW(NULL, csidl, NULL, 0, utf16Path) == S_OK)
    {
        auto utf16PathLen = std::wcslen(utf16Path);
        bool isConvertSucceed = UTF16LE::ConvertTo<UTF8>(std::wstring_view(utf16Path, utf16PathLen), destStr, MAX_PATH) != -1;
        if (isConvertSucceed)
        {
            return static_cast<int32_t>(utf16PathLen);
        }
    }

    return -1;
}

TGON_API int32_t Path::GetUserDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_PROFILE, destStr);   
}

TGON_API int32_t Path::GetDesktopDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_DESKTOP, destStr);
}

TGON_API int32_t Path::GetFontsDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_FONTS, destStr);
}

TGON_API int32_t Path::GetMusicDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_MYMUSIC, destStr);
}
 
TGON_API int32_t Path::GetPicturesDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_MYPICTURES, destStr);
}

TGON_API int32_t Path::GetVideosDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_MYVIDEO, destStr);
}
    
TGON_API int32_t Path::GetDocumentsDirectory(char* destStr)
{
    return GetSpecialDirectory(CSIDL_MYDOCUMENTS, destStr);
}

}
