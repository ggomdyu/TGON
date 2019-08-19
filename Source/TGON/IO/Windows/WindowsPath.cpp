#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"

#include "../Path.h"

namespace tgon
{

extern std::array<wchar_t, 16384> g_tempUtf16Buffer;

int32_t Path::GetFullPath(const std::string_view& path, char* destStr, int32_t destStrBufferSize)
{
    wchar_t utf16Path[512] {};
    if (UTF8::ConvertTo<UTF16LE>(path, utf16Path, std::extent_v<decltype(utf16Path)>) == -1)
    {
        return -1;
    }

    wchar_t utf16DestStr[MAX_PATH] {};
    auto utf16DestStrLen = GetFullPathNameW(utf16Path, std::extent_v<decltype(utf16DestStr)> -1, utf16DestStr, nullptr);
    if (utf16DestStrLen == 0)
    {
        return -1;
    }
    
    auto destStrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(utf16DestStr, utf16DestStrLen), destStr, destStrBufferSize);
    if (destStrLen == -1)
    {

        return -1;
    }

    return static_cast<int32_t>(destStrLen);
}

} /* namespace tgon */
