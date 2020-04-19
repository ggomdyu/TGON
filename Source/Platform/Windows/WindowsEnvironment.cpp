#include "PrecompiledHeader.h"

#include <sstream>
#include <array>
#include <Platform/Windows/Windows.h>
#ifndef SECURITY_WIN32
#   define SECURITY_WIN32
#endif
#include <security.h>
#include <shlobj.h>
#include <Psapi.h>
#pragma pack(push, before_imagehlp, 8)
#include <imagehlp.h>
#pragma pack(pop, before_imagehlp)

#include "../Environment.h"

#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")

#define TGON_THROW_SEH_EXCEPTION() volatile int temp = 0; temp = 1 / temp;

namespace tg
{

thread_local std::array<wchar_t, 16383> g_tempUtf16Buffer;

bool Environment::SetEnvironmentVariable(const char* name, const char* value)
{
    wchar_t utf16Name[2048];
    if (MultiByteToWideChar(CP_UTF8, 0, name, -1, utf16Name, std::extent_v<decltype(utf16Name)>) == 0)
    {
        return false;
    }

    wchar_t utf16Value[4096];
    if (MultiByteToWideChar(CP_UTF8, 0, value, -1, utf16Value, std::extent_v<decltype(utf16Value)>) == 0)
    {
        return false;
    }

    return SetEnvironmentVariableW(utf16Name, utf16Value) == TRUE;
}

std::optional<int32_t> Environment::GetEnvironmentVariable(const char* name, char* destStr, int32_t destStrBufferLen)
{
    wchar_t utf16Name[2048];
    if (MultiByteToWideChar(CP_UTF8, 0, name, -1, utf16Name, std::extent_v<decltype(utf16Name)>) == 0)
    {
        return {};
    }

    wchar_t utf16Value[4096];
    if (GetEnvironmentVariableW(&utf16Name[0], utf16Value, std::extent_v<decltype(utf16Value)>) == 0)
    {
        return {};
    }

    auto utf8ValueLen = WideCharToMultiByte(CP_UTF8, 0, utf16Value, -1, destStr, destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8ValueLen == -1)
    {
        return {};
    }

    return utf8ValueLen;
}

std::optional<int32_t> Environment::GetEnvironmentVariable(const char* name, const gsl::span<char>& destStr)
{
    return Environment::GetEnvironmentVariable(name, &destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferLen)
{
    wchar_t utf16FolderPath[2048];
    if (SHGetFolderPathW(nullptr, static_cast<int>(folder), nullptr, 0, utf16FolderPath) == S_OK)
    {
        auto utf16FolderPathLen = WideCharToMultiByte(CP_UTF8, 0, utf16FolderPath, -1, destStr, destStrBufferLen, nullptr, nullptr) - 1;
        if (utf16FolderPathLen >= 0)
        {
            return utf16FolderPathLen;
        }
    }

    return {};
}

std::optional<int32_t> Environment::GetFolderPath(SpecialFolder folder, const gsl::span<char>& destStr)
{
    return Environment::GetFolderPath(folder, &destStr[0], static_cast<int32_t>(destStr.size()));
}

const std::string& Environment::GetCommandLine()
{
    static auto commandLine = []()
    {
        const wchar_t* utf16CommandLine = GetCommandLineW();

        auto utf16CommandLineBytes = WideCharToMultiByte(CP_UTF8, 0, utf16CommandLine, -1, nullptr, 0, nullptr, nullptr);
        if (utf16CommandLineBytes == 0)
        {
            return std::string();
        }

        std::string utf8CommandLine;
        utf8CommandLine.resize(utf16CommandLineBytes - 1);
        if (WideCharToMultiByte(CP_UTF8, 0, utf16CommandLine, -1, &utf8CommandLine[0], utf8CommandLine.length() + 1, nullptr, nullptr) == 0)
        {
            return std::string();
        }

        return utf8CommandLine;
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

void Environment::FailFast(const char* message, const std::exception& exception)
{
    wchar_t utf16Message[4096] {};
    auto utf16MessageLen = MultiByteToWideChar(CP_UTF8, 0, message, -1, utf16Message, std::extent_v<decltype(utf16Message)>) - 1;
    utf16Message[utf16MessageLen] = '\n';

    OutputDebugStringW(L"FailFast:\n");
    OutputDebugStringW(&utf16Message[0]);

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

std::optional<int32_t> Environment::GetUserName(char* destStr, int32_t destStrBufferLen)
{
    wchar_t utf16UserName[2048];
    auto utf16UserNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16UserName)>);
    if (GetUserNameW(&utf16UserName[0], &utf16UserNameBufferLen) == FALSE)
    {
        return {};
    }

    auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16UserName[0], -1, destStr, destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8UserNameLen == -1)
    {
        return {};
    }

    return utf8UserNameLen;
}

std::optional<int32_t> Environment::GetUserName(const gsl::span<char>& destStr)
{
    return Environment::GetUserName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetMachineName(char* destStr, int32_t destStrBufferLen)
{
    wchar_t utf16ComputerName[2048];
    auto utf16ComputerNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16ComputerName)>);
    if (GetComputerNameW(&utf16ComputerName[0], &utf16ComputerNameBufferLen) == FALSE)
    {
        return {};
    }

    auto utf8ComputerNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16ComputerName[0], -1, destStr, destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8ComputerNameLen == -1)
    {
        return {};
    }

    return utf8ComputerNameLen;
}

std::optional<int32_t> Environment::GetMachineName(const gsl::span<char>& destStr)
{
    return Environment::GetMachineName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetUserDomainName(char* destStr, int32_t destStrBufferLen)
{
    wchar_t utf16UserName[2048];
    auto utf16UserNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16UserName)>);
    if (GetUserNameExW(NameSamCompatible, &utf16UserName[0], &utf16UserNameBufferLen) == TRUE)
    {
        if (const wchar_t* str = wcschr(&utf16UserName[0], '\\'); str != nullptr)
        {
            auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16UserName[0], str - utf16UserName, destStr, destStrBufferLen, nullptr, nullptr);
            if (utf8UserNameLen == 0)
            {
                return {};
            }

            destStr[utf8UserNameLen] = '\0';
            return utf8UserNameLen;
        }
    }

    utf16UserNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16UserName)>);

    if (GetUserNameW(&utf16UserName[0], &utf16UserNameBufferLen) == TRUE)
    {
        SID_NAME_USE peUse;
        wchar_t sid[1024];
        DWORD sidLen = std::extent_v<decltype(sid)>;
        wchar_t utf16AccountName[2048];
        auto utf16AccountNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16UserName)>);
        if (LookupAccountNameW(nullptr, utf16UserName, sid, &sidLen, &utf16AccountName[0], &utf16AccountNameBufferLen, &peUse) == TRUE)
        {
            auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16AccountName[0], -1, destStr, destStrBufferLen, nullptr, nullptr) - 1;
            if (utf8UserNameLen == -1)
            {
                return {};
            }

            destStr[utf8UserNameLen] = '\0';
            return utf8UserNameLen;
        }
    }

    return {};
}

std::optional<int32_t> Environment::GetUserDomainName(const gsl::span<char>& destStr)
{
    return Environment::GetUserDomainName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

DWORD InternalGetStackTrace(EXCEPTION_POINTERS* ep, char* destStr, int32_t destStrBufferLen, int32_t* destStrLen)
{
    HANDLE threadHandle = GetCurrentThread();
    HANDLE processHandle = GetCurrentProcess();
    if (SymInitialize(processHandle, nullptr, false) == FALSE)
    {
        *destStrLen = 0;
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
    EnumProcessModules(processHandle, &moduleHandles[0], static_cast<DWORD>(moduleHandles.size() * sizeof(HMODULE)), &moduleHandlesSize);

    void* baseModuleAddress = nullptr;
    for (auto iter = moduleHandles.rbegin(); iter != moduleHandles.rend(); ++iter)
    {
        HMODULE moduleHandle = *iter;
        MODULEINFO moduleInfo;
        GetModuleInformation(processHandle, moduleHandle, &moduleInfo, sizeof(moduleInfo));

        std::array<char, 4096> imageName;
        GetModuleFileNameExA(processHandle, moduleHandle, &imageName[0], sizeof(imageName));
        std::array<char, 4096> moduleName;
        GetModuleBaseNameA(processHandle, moduleHandle, &moduleName[0], sizeof(moduleName));

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
            IMAGEHLP_SYMBOL64* sym = reinterpret_cast<IMAGEHLP_SYMBOL64*>(&symBytes[0]);
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

            *destStrLen += sprintf_s(destStr + *destStrLen, static_cast<size_t>(destStrBufferLen) - *destStrLen, "   at %s in %s:line %d\n", &undecoratedName[0], line.FileName, line.LineNumber);
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
    int32_t destStrLen = 0;
    __try { TGON_THROW_SEH_EXCEPTION(); }
    __except (InternalGetStackTrace(GetExceptionInformation(), destStr, destStrBufferLen, &destStrLen)) {}

    return destStrLen;
}

bool Environment::GetUserInteractive()
{
    static HWINSTA cachedWindowStationHandle = 0;
    static bool isUserNonInteractive = false;

    auto windowStationHandle = GetProcessWindowStation();
    if (windowStationHandle != 0 && windowStationHandle != cachedWindowStationHandle)
    {
        USEROBJECTFLAGS flags;
        DWORD needLength;
        if (GetUserObjectInformationW(windowStationHandle, UOI_FLAGS, reinterpret_cast<PVOID>(&flags), sizeof(flags), &needLength) == TRUE)
        {
            if ((flags.dwFlags & WSF_VISIBLE) == 0)
            {
                isUserNonInteractive = true;
            }
        }

        cachedWindowStationHandle = windowStationHandle;
    }

    return !isUserNonInteractive;
}

}

#undef TGON_THROW_SEH_EXCEPTION