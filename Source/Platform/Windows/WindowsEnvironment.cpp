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

bool Environment::SetEnvironmentVariable(const char8_t* name, const char8_t* value)
{
    std::array<wchar_t, 2048> utf16Name{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(name), -1, &utf16Name[0], static_cast<int>(utf16Name.size()) == 0))
    {
        return false;
    }

    std::array<wchar_t, 4096> utf16Value{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(value), -1, &utf16Value[0], static_cast<int>(utf16Value.size())) == 0)
    {
        return false;
    }

    return SetEnvironmentVariableW(&utf16Name[0], &utf16Value[0]) == TRUE;
}

std::optional<int32_t> Environment::GetEnvironmentVariable(const char8_t* name, char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16Name{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(name), -1, &utf16Name[0], static_cast<DWORD>(utf16Name.size())) == 0)
    {
        return {};
    }

    std::array<wchar_t, 4096> utf16Value{};
    if (GetEnvironmentVariableW(&utf16Name[0], &utf16Value[0], static_cast<DWORD>(utf16Value.size())) == 0)
    {
        return {};
    }

    const auto utf8ValueLen = WideCharToMultiByte(CP_UTF8, 0, &utf16Value[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8ValueLen == -1)
    {
        return {};
    }

    return utf8ValueLen;
}

std::optional<int32_t> Environment::GetEnvironmentVariable(const char8_t* name, const std::span<char8_t>& destStr)
{
    return GetEnvironmentVariable(name, &destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetFolderPath(SpecialFolder folder, char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16FolderPath{};
    if (SHGetFolderPathW(nullptr, static_cast<int>(folder), nullptr, 0, &utf16FolderPath[0]) == S_OK)
    {
        const auto utf16FolderPathLen = WideCharToMultiByte(CP_UTF8, 0, &utf16FolderPath[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
        if (utf16FolderPathLen >= 0)
        {
            return utf16FolderPathLen;
        }
    }

    return {};
}

std::optional<int32_t> Environment::GetFolderPath(SpecialFolder folder, const std::span<char8_t>& destStr)
{
    return GetFolderPath(folder, &destStr[0], static_cast<int32_t>(destStr.size()));
}

const std::u8string& Environment::GetCommandLine()
{
    static auto commandLine = []()
    {
        const wchar_t* utf16CommandLine = GetCommandLineW();

        const auto utf16CommandLineByteCount = WideCharToMultiByte(CP_UTF8, 0, utf16CommandLine, -1, nullptr, 0, nullptr, nullptr);
        if (utf16CommandLineByteCount == 0)
        {
            return std::u8string();
        }

        std::u8string utf8CommandLine;
        utf8CommandLine.resize(static_cast<size_t>(utf16CommandLineByteCount) - 1);
        if (WideCharToMultiByte(CP_UTF8, 0, utf16CommandLine, -1, reinterpret_cast<char*>(&utf8CommandLine[0]), utf8CommandLine.length() + 1, nullptr, nullptr) == 0)
        {
            return std::u8string();
        }

        return utf8CommandLine;
    } ();
    return commandLine;
}

const std::vector<std::u8string>& Environment::GetCommandLineArgs()
{
    static auto commandLineArgs = []()
    {
        std::vector<std::u8string> ret;
        
        std::basic_stringstream<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>> ss(GetCommandLine());
        std::u8string commandLineArg;
        while (std::getline(ss, commandLineArg, u8' '))
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

void Environment::FailFast(const char8_t* message, const std::exception& exception)
{
    std::array<wchar_t, 4096> utf16Message{};
    const auto utf16MessageLen = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(message), -1, &utf16Message[0], std::extent_v<decltype(utf16Message)>) - 1;
    utf16Message[utf16MessageLen] = '\n';

    OutputDebugStringW(L"FailFast:\n");
    OutputDebugStringW(&utf16Message[0]);

    throw exception;
}

std::u8string_view Environment::GetNewLine()
{
    char8_t newLine[] = u8"\r\n";
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

std::optional<int32_t> Environment::GetUserName(char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16UserName{};
    auto utf16UserNameBufferLen = static_cast<DWORD>(std::extent_v<decltype(utf16UserName)>);
    if (GetUserNameW(&utf16UserName[0], &utf16UserNameBufferLen) == FALSE)
    {
        return {};
    }

    const auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16UserName[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8UserNameLen == -1)
    {
        return {};
    }

    return utf8UserNameLen;
}

std::optional<int32_t> Environment::GetUserName(const std::span<char8_t>& destStr)
{
    return GetUserName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetMachineName(char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16ComputerName{};
    auto utf16ComputerNameBufferLen = static_cast<DWORD>(utf16ComputerName.size());
    if (GetComputerNameW(&utf16ComputerName[0], &utf16ComputerNameBufferLen) == FALSE)
    {
        return {};
    }

    const auto utf8ComputerNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16ComputerName[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8ComputerNameLen == -1)
    {
        return {};
    }

    return utf8ComputerNameLen;
}

std::optional<int32_t> Environment::GetMachineName(const std::span<char8_t>& destStr)
{
    return GetMachineName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

std::optional<int32_t> Environment::GetUserDomainName(char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16UserName{};
    auto utf16UserNameBufferLen = static_cast<DWORD>(utf16UserName.size());
    if (GetUserNameExW(NameSamCompatible, &utf16UserName[0], &utf16UserNameBufferLen) == TRUE)
    {
        if (const wchar_t* str = wcschr(&utf16UserName[0], L'\\'); str != nullptr)
        {
            const auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16UserName[0], str - &utf16UserName[0], reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr);
            if (utf8UserNameLen == 0)
            {
                return {};
            }

            destStr[utf8UserNameLen] = u8'\0';
            return utf8UserNameLen;
        }
    }

    utf16UserNameBufferLen = static_cast<DWORD>(utf16UserName.size());

    if (GetUserNameW(&utf16UserName[0], &utf16UserNameBufferLen) == TRUE)
    {
        SID_NAME_USE peUse;
        std::array<wchar_t, 1024> sid{};
        auto sidLen = static_cast<DWORD>(sid.size());
        std::array<wchar_t, 2048> utf16AccountName{};
        auto utf16AccountNameBufferLen = static_cast<DWORD>(utf16UserName.size());
        if (LookupAccountNameW(nullptr, &utf16UserName[0], &sid[0], &sidLen, &utf16AccountName[0], &utf16AccountNameBufferLen, &peUse) == TRUE)
        {
            const auto utf8UserNameLen = WideCharToMultiByte(CP_UTF8, 0, &utf16AccountName[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
            if (utf8UserNameLen == -1)
            {
                return {};
            }

            destStr[utf8UserNameLen] = u8'\0';
            return utf8UserNameLen;
        }
    }

    return {};
}

std::optional<int32_t> Environment::GetUserDomainName(const std::span<char8_t>& destStr)
{
    return GetUserDomainName(&destStr[0], static_cast<int32_t>(destStr.size()));
}

DWORD InternalGetStackTrace(EXCEPTION_POINTERS* ep, char8_t* destStr, int32_t destStrBufferLen, int32_t* destStrLen)
{
    auto* threadHandle = GetCurrentThread();
    auto* processHandle = GetCurrentProcess();
    if (SymInitialize(processHandle, nullptr, false) == FALSE)
    {
        *destStrLen = 0;
        return EXCEPTION_EXECUTE_HANDLER;
    }

    SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    
    CONTEXT* context = ep->ContextRecord;
#ifdef _M_X64
    STACKFRAME64 frame
    {
        .AddrPC = ADDRESS64{
            .Offset = context->Rip,
            .Mode = AddrModeFlat
        },
        .AddrFrame = ADDRESS64{
            .Offset = context->Rbp,
            .Mode = AddrModeFlat
        },
        .AddrStack = ADDRESS64{
            .Offset = context->Rsp,
            .Mode = AddrModeFlat
        },
    };
#else
    STACKFRAME64 frame
    {
        .AddrPC = ADDRESS64{
            .Offset = context->Eip,
            .Mode = AddrModeFlat
        },
        .AddrFrame = ADDRESS64{
            .Offset = context->Ebp,
            .Mode = AddrModeFlat
        },
        .AddrStack = ADDRESS64{
            .Offset = context->Esp,
            .Mode = AddrModeFlat
        },
    };
#endif
    
    std::vector<HMODULE> moduleHandles;
    DWORD moduleHandlesByteCount = 0;
    EnumProcessModules(processHandle, nullptr, 0, &moduleHandlesByteCount);
    moduleHandles.resize(moduleHandlesByteCount / sizeof(HMODULE));
    EnumProcessModules(processHandle, &moduleHandles[0], static_cast<DWORD>(moduleHandles.size() * sizeof(HMODULE)), &moduleHandlesByteCount);

    void* baseModuleAddress = nullptr;
    for (auto it = moduleHandles.rbegin(); it != moduleHandles.rend(); ++it)
    {
        const HMODULE moduleHandle = *it;
        MODULEINFO moduleInfo;
        GetModuleInformation(processHandle, moduleHandle, &moduleInfo, sizeof(moduleInfo));

        std::array<char8_t, 4096> imageName{};
        GetModuleFileNameExA(processHandle, moduleHandle, reinterpret_cast<char*>(&imageName[0]), sizeof(imageName));
        std::array<char8_t, 4096> moduleName{};
        GetModuleBaseNameA(processHandle, moduleHandle, reinterpret_cast<char*>(&moduleName[0]), sizeof(moduleName));

        SymLoadModule64(processHandle, 0, reinterpret_cast<char*>(&imageName[0]), reinterpret_cast<char*>(&moduleName[0]), reinterpret_cast<DWORD64>(moduleInfo.lpBaseOfDll), moduleInfo.SizeOfImage);

        baseModuleAddress = moduleInfo.lpBaseOfDll;
    }

    const PIMAGE_NT_HEADERS image = ImageNtHeader(baseModuleAddress);
    const DWORD imageType = image->FileHeader.Machine;

    IMAGEHLP_LINE64 line {};
    line.SizeOfStruct = sizeof(line);
    
    DWORD64 displacement = 0;
    DWORD offsetFromSymbol = 0;
    std::array<char8_t, 1024> undecoratedName{};

    *destStrLen = 0;

    do
    {
        if (frame.AddrPC.Offset != 0)
        {
            std::array<std::byte, sizeof(IMAGEHLP_SYMBOL64) + 1024> symBytes{};
            auto* sym = reinterpret_cast<IMAGEHLP_SYMBOL64*>(&symBytes[0]);
            sym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
            sym->MaxNameLength = static_cast<DWORD>(undecoratedName.size());
            SymGetSymFromAddr64(processHandle, frame.AddrPC.Offset, &displacement, sym);

            // Get the undecorated name of function
            if (UnDecorateSymbolName(sym->Name, reinterpret_cast<char*>(&undecoratedName[0]), sym->MaxNameLength, UNDNAME_COMPLETE) == FALSE)
            {
                continue;
            }
            
            // Get the file name and line
            SymGetLineFromAddr64(processHandle, frame.AddrPC.Offset, &offsetFromSymbol, &line);

            *destStrLen += sprintf_s(reinterpret_cast<char*>(destStr) + *destStrLen, static_cast<size_t>(destStrBufferLen) - *destStrLen, "   at %s in %s:line %d\n", reinterpret_cast<const char*>(&undecoratedName[0]), line.FileName, line.LineNumber);
        }

        if (StackWalk64(imageType, processHandle, threadHandle, &frame, context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr) == FALSE)
        {
            break;
        }
    } while (frame.AddrReturn.Offset != 0);

    SymCleanup(processHandle);

    return EXCEPTION_EXECUTE_HANDLER;
}

int32_t Environment::GetStackTrace(char8_t* destStr, int32_t destStrBufferLen)
{
    int32_t destStrLen = 0;
    __try
    {
        TGON_THROW_SEH_EXCEPTION();
    }
    __except (InternalGetStackTrace(GetExceptionInformation(), destStr, destStrBufferLen, &destStrLen))
    {
    }

    return destStrLen;
}

bool Environment::GetUserInteractive()
{
    static HWINSTA cachedWindowStationHandle = 0;
    static bool isUserNonInteractive = false;

    auto* windowStationHandle = GetProcessWindowStation();
    if (windowStationHandle != nullptr && windowStationHandle != cachedWindowStationHandle)
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