#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>
#include <shlobj.h>
#include <array>

#include "String/Encoding.h"

#include "../Environment.h"

namespace tgon
{

thread_local std::array<char, 16384> g_tempUtf8Buffer;
thread_local std::array<wchar_t, 16384> g_tempUtf16Buffer;

int32_t Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferSize)
{
    auto utf16PathLen = GetCurrentDirectoryW(g_tempUtf16Buffer.size(), g_tempUtf16Buffer.data());
    if (utf16PathLen != 0)
    {
        auto utf8PathLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(&g_tempUtf16Buffer[0], utf16PathLen), &destStr[0], destStrBufferSize);
        if (utf8PathLen != -1)
        {
            return utf8PathLen;
        }
    }

    return -1;
}

int32_t Environment::GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferSize)
{
    if (SHGetFolderPathW(nullptr, static_cast<int>(folder), nullptr, 0, g_tempUtf16Buffer.data()) == S_OK)
    {
        auto utf8PathLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(g_tempUtf16Buffer.data()), destStr, destStrBufferSize);
        if (utf8PathLen != -1)
        {
            return utf8PathLen;
        }
    }

    return -1;
}

const std::string& Environment::GetCommandLine()
{
    static auto commandLine = []()
    {
        return Encoding<UTF16LE>::ConvertTo<UTF8>(std::wstring_view(GetCommandLineW()));
    } ();

    return commandLine;
}

int64_t Environment::GetTickCount()
{
    return static_cast<int64_t>(::GetTickCount());
}

bool Environment::Is64BitProcess()
{
#if defined(_WIN64)
    return true;
#else
    return false;
#endif
}

bool Environment::Is64BitOperatingSystem()
{
#if defined(_WIN64)
    // 64-bit programs run only on 64-bit 
    return true;
#else
    BOOL isWow64 = FALSE;
    return IsWow64Process(GetCurrentProcess(), &isWow64) && isWow64;
#endif
}

std::string_view Environment::GetNewLine()
{
    char newLine[] = "\r\n";
    return {newLine, std::extent_v<decltype(newLine)> - 1};
}

} /* namespace tgon */