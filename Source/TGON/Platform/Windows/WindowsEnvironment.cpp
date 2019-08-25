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

thread_local std::array<wchar_t, 32767> g_tempUtf16Buffer;

bool Environment::SetEnvironmentVariable(const std::string_view& name, const std::string_view& value)
{
    auto utf16Name = UTF8::ConvertTo<UTF16LE>(name);
    auto utf16Value = UTF8::ConvertTo<UTF16LE>(value);

    return SetEnvironmentVariableW(reinterpret_cast<const wchar_t*>(utf16Name.c_str()), reinterpret_cast<const wchar_t*>(utf16Value.c_str())) == TRUE;
}

int32_t Environment::GetEnvironmentVariable(const std::string_view& name, char* destStr, int32_t destStrBufferLen)
{
    // todo: impl
    return -1;
}

int32_t Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    auto utf16StrLen = GetCurrentDirectoryW(g_tempUtf16Buffer.size(), g_tempUtf16Buffer.data());
    if (utf16StrLen != 0)
    {
        auto utf8StrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(&g_tempUtf16Buffer[0], utf16StrLen), &destStr[0], destStrBufferLen);
        if (utf8StrLen != -1)
        {
            return utf8StrLen;
        }
    }

    return -1;
}

int32_t Environment::GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferLen)
{
    if (SHGetFolderPathW(nullptr, static_cast<int>(folder), nullptr, 0, g_tempUtf16Buffer.data()) == S_OK)
    {
        auto utf8StrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(g_tempUtf16Buffer.data()), destStr, destStrBufferLen);
        if (utf8StrLen != -1)
        {
            return utf8StrLen;
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

int32_t Environment::GetSystemPageSize()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    return static_cast<int32_t>(si.dwPageSize);
}

int32_t Environment::GetCurrentManagedThreadId()
{
    return GetCurrentThreadId();
}

int32_t Environment::GetUserName(char* destStr, int32_t destStrBufferLen)
{
    DWORD utf16StrLen = 0;
    if (GetUserNameW(g_tempUtf16Buffer.data(), &utf16StrLen) == TRUE)
    {
        auto utf8StrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(&g_tempUtf16Buffer[0], utf16StrLen), &destStr[0], destStrBufferLen);
        if (utf8StrLen != -1)
        {
            return utf8StrLen;
        }
    }

    return -1;
}

int32_t Environment::GetMachineName(char* destStr, int32_t destStrBufferLen)
{
    DWORD utf16StrLen = 0;
    if (GetComputerNameW(g_tempUtf16Buffer.data(), &utf16StrLen) == TRUE)
    {
        auto utf8StrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(&g_tempUtf16Buffer[0], utf16StrLen), &destStr[0], destStrBufferLen);
        if (utf8StrLen != -1)
        {
            return utf8StrLen;
        }
    }

    return -1;
}

int32_t tgon::Environment::GetUserDomainName(char* destStr, int32_t destStrBufferLen)
{
    DWORD utf16StrLen = 0;
    if (GetUserNameW(g_tempUtf16Buffer.data(), &utf16StrLen) == TRUE)
    {
        auto utf8StrLen = UTF16LE::ConvertTo<UTF8>(std::wstring_view(&g_tempUtf16Buffer[0], utf16StrLen), &destStr[0], destStrBufferLen);
        if (utf8StrLen != -1)
        {
            return utf8StrLen;
        }
    }

    return -1;
}
    
} /* namespace tgon */
