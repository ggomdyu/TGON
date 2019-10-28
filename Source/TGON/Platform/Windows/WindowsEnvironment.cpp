#include "PrecompiledHeader.h"

#include <Windows.h>
#ifndef SECURITY_WIN32
#   define SECURITY_WIN32
#endif
#include <security.h>
#include <shlobj.h>
#include <Psapi.h>
#include <array>
#include <sstream>

#pragma pack(push, before_imagehlp, 8)
#include <imagehlp.h>
#pragma pack(pop, before_imagehlp)

#include "Diagnostics/Debug.h"
#include "String/Encoding.h"

#include "../Environment.h"

#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")

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

int32_t Environment::GetEnvironmentVariable(const std::string_view& name, const gsl::span<char>& destStr)
{
    return GetEnvironmentVariable(name, &destStr[0], destStr.size());
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

int32_t Environment::GetFolderPath(SpecialFolder folder, const gsl::span<char>& destStr)
{
    return GetFolderPath(folder, &destStr[0], destStr.size());
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

const std::vector<std::string>& Environment::GetCommandLineArgs()
{
    static auto commandLineArgs = []()
    {
        std::vector<std::string> ret;
        
        std::stringstream ss(GetCommandLine());
        std::string commandLineArg;
        while (std::getline(ss, commandLineArg, ' '))
        {
            ret.push_back(std::move(commandLineArg));
        }
        
        return ret;
    } ();
    
    return commandLineArgs;
}

int64_t Environment::GetTickCount()
{
    return static_cast<int64_t>(::GetTickCount64());
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

void Environment::FailFast(const std::string_view& message)
{
    FailFast(message, {});
}

void Environment::FailFast(const std::string_view& message, const std::exception& exception)
{
    auto utf16Message = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(message.data()), static_cast<int32_t>(message.size()));
    utf16Message.insert(utf16Message.end(), { std::byte('\n'), std::byte(0), std::byte(0), std::byte(0) });

    OutputDebugStringW(L"FailFast:\n");
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(utf16Message.data()));

    throw exception;
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

int32_t Environment::GetUserName(const gsl::span<char>& destStr)
{
    return GetUserName(&destStr[0], destStr.size());
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

int32_t Environment::GetMachineName(const gsl::span<char>& destStr)
{
    return GetMachineName(&destStr[0], destStr.size());
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

int32_t Environment::GetUserDomainName(const gsl::span<char>& destStr)
{
    return GetUserDomainName(&destStr[0], destStr.size());
}

DWORD InternalGetStackTrace(EXCEPTION_POINTERS* ep, char* destStr, int32_t destStrBufferLen, int32_t* destStrLen)
{
    HANDLE threadHandle = GetCurrentThread();
    HANDLE processHandle = GetCurrentProcess();
    if (SymInitialize(processHandle, nullptr, false) == FALSE)
    {
        *destStrLen = -1;
        return EXCEPTION_EXECUTE_HANDLER;
    }

    SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    
    CONTEXT* context = ep->ContextRecord;
#ifdef _M_X64
    STACKFRAME64 frame;
    frame.AddrPC.Offset = context->Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;
#else
    STACKFRAME64 frame;
    frame.AddrPC.Offset = context->Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Esp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
#endif
    
    std::vector<HMODULE> moduleHandles;
    DWORD moduleHandlesSize = 0;
    EnumProcessModules(processHandle, nullptr, 0, &moduleHandlesSize);
    moduleHandles.resize(moduleHandlesSize / sizeof(HMODULE));
    EnumProcessModules(processHandle, &moduleHandles[0], moduleHandles.size() * sizeof(HMODULE), &moduleHandlesSize);

    void* baseModuleAddress = nullptr;
    for (auto iter = moduleHandles.rbegin(); iter != moduleHandles.rend(); ++iter)
    {
        HMODULE moduleHandle = *iter;
        MODULEINFO moduleInfo;
        GetModuleInformation(processHandle, moduleHandle, &moduleInfo, sizeof(moduleInfo));

        std::array<char, 4096> imageName;
        GetModuleFileNameExA(processHandle, moduleHandle, imageName.data(), sizeof(imageName));
        std::array<char, 4096> moduleName;
        GetModuleBaseNameA(processHandle, moduleHandle, moduleName.data(), sizeof(moduleName));

        SymLoadModule64(processHandle, 0, &imageName[0], &moduleName[0], reinterpret_cast<DWORD64>(moduleInfo.lpBaseOfDll), moduleInfo.SizeOfImage);

        baseModuleAddress = moduleInfo.lpBaseOfDll;
    }

    PIMAGE_NT_HEADERS image = ImageNtHeader(baseModuleAddress);
    DWORD imageType = image->FileHeader.Machine;

    IMAGEHLP_LINE64 line {};
    line.SizeOfStruct = sizeof(line);
    
    DWORD64 displacement = 0;
    DWORD offsetFromSymbol = 0;
    std::array<char, 1024> undecoratedName;

    *destStrLen = 0;

    do
    {
        if (frame.AddrPC.Offset != 0)
        {
            std::array<std::byte, sizeof(IMAGEHLP_SYMBOL64) + 1024> symBytes {};
            IMAGEHLP_SYMBOL64* sym = reinterpret_cast<IMAGEHLP_SYMBOL64*>(symBytes.data());
            sym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
            sym->MaxNameLength = static_cast<DWORD>(undecoratedName.size());
            SymGetSymFromAddr64(processHandle, frame.AddrPC.Offset, &displacement, sym);

            // Get the undecorated name of function
            if (UnDecorateSymbolName(sym->Name, &undecoratedName[0], sym->MaxNameLength, UNDNAME_COMPLETE) == FALSE)
            {
                continue;
            }
            
            // Get the file name and line
            SymGetLineFromAddr64(processHandle, frame.AddrPC.Offset, &offsetFromSymbol, &line);

            *destStrLen += sprintf_s(destStr + *destStrLen, destStrBufferLen - *destStrLen, "   at %s in %s:line %d\n", undecoratedName.data(), line.FileName, line.LineNumber);
        }

        if (StackWalk64(imageType, processHandle, threadHandle, &frame, context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr) == FALSE)
        {
            break;
        }
    } while (frame.AddrReturn.Offset != 0);

    SymCleanup(processHandle);

    return EXCEPTION_EXECUTE_HANDLER;
}

int32_t Environment::GetStackTrace(char* destStr, int32_t destStrBufferLen)
{
    int32_t ret;

    __try {
        volatile int temp = 0;
        temp = 1 / temp;
    }
    __except (InternalGetStackTrace(GetExceptionInformation(), destStr, destStrBufferLen, &ret)) 
    {
    }

    return ret;
}

} /* namespace tgon */
