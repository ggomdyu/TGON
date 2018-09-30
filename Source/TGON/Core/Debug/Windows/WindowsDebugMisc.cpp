#include "PrecompiledHeader.h"

#include <Windows.h>

#include "WindowsDebugMisc.h"

namespace tgon
{

#if defined(_M_X64) || defined(_M_IX86)
bool PreventSetUnhandledExceptionFilter()
{
    HMODULE kernel32Handle = LoadLibraryW(L"kernel32.dll");
    if (kernel32Handle == nullptr)
    {
        return false;
    }

    void* orgEntry = GetProcAddress(kernel32Handle, "SetUnhandledExceptionFilter");
    if (orgEntry == nullptr)
    {
        return false;
    }

#ifdef _M_IX86
    // Code for x86:
    // 33 C0                xor         eax,eax
    // C2 04 00             ret         4
    unsigned char szExecute[] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };
#elif _M_X64
    // 33 C0                xor         eax,eax
    // C3                   ret
    unsigned char szExecute[] = { 0x33, 0xC0, 0xC3 };
#else
#error "The following code only works for x86 and x64!"
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
}
#else
#pragma message("This code works only for x86 and x64!")
#endif

} /* namespace tgon */
