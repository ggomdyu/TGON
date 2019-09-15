#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>
#ifndef SECURITY_WIN32
#   define SECURITY_WIN32
#endif
#include <security.h>
#include <shlobj.h>
#include <array>

#include "String/Encoding.h"

#include "../Environment.h"

#pragma comment(lib, "Secur32.lib")

namespace tgon
{

thread_local std::array<wchar_t, 32767> g_tempUtf16Buffer;

bool Environment::SetEnvironmentVariable(const std::string_view& name, const std::string_view& value)
{
    const wchar_t* utf16Name = &g_tempUtf16Buffer[0];
    auto utf16NameBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(name.data()), static_cast<int32_t>(name.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16NameBytes == -1)
    {
        return false;
    }

    auto utf16NameLen = utf16NameBytes / 2;
    const wchar_t* utf16Value = &g_tempUtf16Buffer[utf16NameLen + 1];
    auto utf16ValueBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&value[0]), static_cast<int32_t>(value.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[utf16NameLen + 1]), static_cast<int32_t>(g_tempUtf16Buffer.size() - (utf16NameBytes + sizeof(wchar_t))));
    if (utf16ValueBytes == -1)
    {
        return false;
    }

    return SetEnvironmentVariableW(utf16Name, utf16Value) == TRUE;
}

int32_t Environment::GetEnvironmentVariable(const std::string_view& name, char* destStr, int32_t destStrBufferLen)
{
    do
    {
        const wchar_t* utf16Name = &g_tempUtf16Buffer[0];
        auto utf16NameBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(name.data()), static_cast<int32_t>(name.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
        if (utf16NameBytes == -1)
        {
            break;
        }

        auto utf16NameLen = utf16NameBytes / 2;
        const wchar_t* utf16Value = &g_tempUtf16Buffer[utf16NameLen + 1];
        DWORD utf16ValueLen = GetEnvironmentVariableW(utf16Name, &g_tempUtf16Buffer[utf16NameLen + 1], static_cast<DWORD>(g_tempUtf16Buffer.size() - (utf16NameBytes + sizeof(wchar_t))));
        if (utf16ValueLen == 0)
        {
            break;
        }

        auto utf8StrLen = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(utf16Value), static_cast<int32_t>(utf16ValueLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen);
        if (utf8StrLen >= 0)
        {
            return utf8StrLen;
        }
    }
    while (false);

    return -1;
}

int32_t Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    auto utf16StrLen = GetCurrentDirectoryW(g_tempUtf16Buffer.size(), g_tempUtf16Buffer.data());
    if (utf16StrLen == 0)
    {
        return -1;
    }
    
    auto utf8StrLen = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16StrLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen);
    if (utf8StrLen >= 0)
    {
        return utf8StrLen;
    }

    return -1;
}

int32_t Environment::GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferLen)
{
    if (SHGetFolderPathW(nullptr, static_cast<int>(folder), nullptr, 0, g_tempUtf16Buffer.data()) == S_OK)
    {
        auto utf8StrLen = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(wcslen(&g_tempUtf16Buffer[0]) * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen);
        if (utf8StrLen >= 0)
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
        std::wstring_view commandLine = GetCommandLineW();

        auto utf8Str = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&commandLine[0]), static_cast<int32_t>(commandLine.size() * 2));
        return std::string(reinterpret_cast<const char*>(utf8Str.data()), utf8Str.size());
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
    DWORD utf16BufferLen = g_tempUtf16Buffer.size();
    if (GetUserNameW(&g_tempUtf16Buffer[0], &utf16BufferLen) == TRUE)
    {
        auto utf8StrBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16BufferLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), static_cast<int32_t>(destStrBufferLen));
        if (utf8StrBytes >= 0)
        {
            return utf8StrBytes;
        }
    }

    return -1;
}

int32_t Environment::GetMachineName(char* destStr, int32_t destStrBufferLen)
{
    DWORD utf16BufferLen = g_tempUtf16Buffer.size();
    if (GetComputerNameW(&g_tempUtf16Buffer[0], &utf16BufferLen) == TRUE)
    {
        auto utf8StrBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16BufferLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), static_cast<int32_t>(destStrBufferLen));
        if (utf8StrBytes >= 0)
        {
            return utf8StrBytes;
        }
    }

    return -1;
}

int32_t Environment::GetUserDomainName(char* destStr, int32_t destStrBufferLen)
{
    DWORD utf16BufferLen = g_tempUtf16Buffer.size();
    if (GetUserNameExW(NameSamCompatible, &g_tempUtf16Buffer[0], &utf16BufferLen) == TRUE)
    {
        if (const wchar_t* str = wcschr(&g_tempUtf16Buffer[0], '\\'); str != nullptr)
        {
            auto utf8StrBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(str - &g_tempUtf16Buffer[0]) * 2, reinterpret_cast<std::byte*>(&destStr[0]), static_cast<int32_t>(destStrBufferLen));
            if (utf8StrBytes >= 0)
            {
                return utf8StrBytes;
            }
        }
    }

    utf16BufferLen = g_tempUtf16Buffer.size();

    wchar_t userName[256];
    DWORD userNameBufferLen = std::extent_v<decltype(userName)>;
    if (GetUserNameW(&userName[0], &userNameBufferLen) == TRUE)
    {
        SID_NAME_USE peUse;
        wchar_t sid[1024];
        DWORD sidLen = std::extent_v<decltype(sid)>;
        if (LookupAccountNameW(nullptr, userName, sid, &sidLen, &g_tempUtf16Buffer[0], &utf16BufferLen, &peUse) == TRUE)
        {
            auto utf8StrBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16BufferLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), static_cast<int32_t>(destStrBufferLen));
            if (utf8StrBytes >= 0)
            {
                return utf8StrBytes;
            }
        }
    }

    return -1;
}
    
} /* namespace tgon */
