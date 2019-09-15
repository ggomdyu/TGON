#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>
#include <StackWalker.h>
#include <array>

#include "String/Encoding.h"

#include "../Debug.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

void Debug::Write(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(message.data()), static_cast<int32_t>(message.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    int32_t utf16MessageLen = utf16MessageBytes / 2;
    for (int32_t i = 0; i < m_indentLevel; ++i)
    {
        g_tempUtf16Buffer[utf16MessageLen + i] = '\t';
    }

    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel] = '\0';

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()));
#endif
}

void Debug::WriteLine(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(message.data()), static_cast<int32_t>(message.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    int32_t utf16MessageLen = utf16MessageBytes / 2;
    for (int32_t i = 0; i < m_indentLevel; ++i)
    {
        g_tempUtf16Buffer[utf16MessageLen + i] = '\t';
    }
    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel] = '\n';
    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel + 1] = '\0';

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()));
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
    BOOL writeProcessMemorySucceed = WriteProcessMemory(GetCurrentProcess(), orgEntry, szExecute, sizeof(szExecute), &bytesWritten);

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
