#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>
#include <StackWalker.h>

#include "String/Encoding.h"

#include "../Debug.h"

namespace tgon
{

void Debug::Write(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16Message = UTF8::ConvertTo<UTF16LE>(message);
    utf16Message.insert(0, m_indentLevel, '\t');

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(utf16Message.data()));
#endif
}

void Debug::WriteLine(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16Message = UTF8::ConvertTo<UTF16LE>(message);
    utf16Message.insert(0, m_indentLevel, '\t');
    utf16Message += u"\n";

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(utf16Message.data()));
#endif
}

void Debug::Assert(bool condition, const std::string_view& message, const std::string_view& detailMessage)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    if (condition)
    {
        return;
    }

    Fail(message, detailMessage);
#endif
}

bool PreventSetUnhandledExceptionFilter()
{
#if defined(_M_X64) || defined(_M_IX86)
    HMODULE kernel32Handle = LoadLibraryW(L"kernel32.dll");
    if (kernel32Handle == nullptr)
    {
        return false;
    }

    void* orgEntry = reinterpret_cast<void*>(GetProcAddress(kernel32Handle, "SetUnhandledExceptionFilter"));
    if (orgEntry == nullptr)
    {
        return false;
    }

#ifdef _M_IX86
    // Code for x86:
    // 33 C0                xor         eax,eax
    // C2 04 00             ret         4
    unsigned char szExecute[] = {0x33, 0xC0, 0xC2, 0x04, 0x00};
#elif _M_X64
    // 33 C0                xor         eax,eax
    // C3                   ret
    unsigned char szExecute[] = {0x33, 0xC0, 0xC3};
#endif

    DWORD oldProtectInfo = 0;
    BOOL protectSucceed = VirtualProtect(orgEntry, sizeof(szExecute), PAGE_EXECUTE_READWRITE, &oldProtectInfo);

    SIZE_T bytesWritten = 0;
    BOOL writeProcessMemorySucceed = WriteProcessMemory(GetCurrentProcess(), orgEntry, szExecute, sizeof(szExecute),
        &bytesWritten);

    if ((protectSucceed != FALSE) && (oldProtectInfo != PAGE_EXECUTE_READWRITE))
    {
        DWORD tempBuffer;
        VirtualProtect(orgEntry, sizeof(szExecute), oldProtectInfo, &tempBuffer);
    }
    
    return (writeProcessMemorySucceed == TRUE) ? true : false;
#else
    return false;
#endif
}

void EnableCrashHandler()
{
    SetUnhandledExceptionFilter([](EXCEPTION_POINTERS * exceptionPointers) -> LONG
    {
        StackWalker stackWalker;
        stackWalker.ShowCallstack(::GetCurrentThread(), exceptionPointers->ContextRecord, 0, 0);

        MessageBox(nullptr, L"HI", L"HI", MB_OK);

        return EXCEPTION_CONTINUE_SEARCH;
    });

    PreventSetUnhandledExceptionFilter();
}

} /* namespace tgon */
