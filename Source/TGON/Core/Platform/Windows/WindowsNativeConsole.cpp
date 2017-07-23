#include "PrecompiledHeader.pch"
#include "WindowsNativeConsole.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

#include "Core/String/TEncoding.h"

namespace tgon
{
namespace platform
{

namespace
{

class WindowsConsoleHelper final
{
/**
 * @section Ctor/Dtor
 */
private:
    WindowsConsoleHelper();
    ~WindowsConsoleHelper();

public:
    static WindowsConsoleHelper* Get();

/**
 * @section Get method
 */
public:
    HANDLE GetConsoleHandle() const;

/**
 * @section Private variables
 */
private:
	HANDLE m_outputHandle;
};

WindowsConsoleHelper::WindowsConsoleHelper()
{
#ifndef TGON_DISABLE_CONSOLE
    bool consoleAlreadyCreated = ::GetConsoleWindow() != nullptr;
    if (!consoleAlreadyCreated)
    {
        if (::AllocConsole() == FALSE)
        {
			assert(false && "Failed to create console.");
		}
	}

    m_outputHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

WindowsConsoleHelper::~WindowsConsoleHelper()
{
#ifndef TGON_DISABLE_CONSOLE
    ::FreeConsole();
#endif
}

WindowsConsoleHelper* WindowsConsoleHelper::Get()
{
    static WindowsConsoleHelper instance;
    return &instance;
}

HANDLE WindowsConsoleHelper::GetConsoleHandle() const
{
    return m_outputHandle;
}

} /*namespace*/

void WindowsNativeConsole::Write(const char* format, ...)
{
#ifndef TGON_DISABLE_CONSOLE
    wchar_t utf16Str[256];
    bool succeed = string::ConvertUTF8ToUTF16(format, reinterpret_cast<char*>(&utf16Str[0])) != -1;
    if (succeed)
    {
        va_list vaList;
        va_start(vaList, format);

        wchar_t destStr[256];
        auto destStrLen = wvsprintfW(destStr, utf16Str, vaList);
            
        ::WriteConsoleW(
            WindowsConsoleHelper::Get()->GetConsoleHandle(),
            destStr,
            destStrLen,
            nullptr,
            nullptr
        );
    }
#endif
}

void WindowsNativeConsole::Write(const wchar_t* format, ...)
{
#ifndef TGON_DISABLE_CONSOLE
    va_list vaList;
    va_start(vaList, format);

    wchar_t destStr[256];
    auto destStrLen = wvsprintfW(destStr, format, vaList);
        
    ::WriteConsoleW(
        WindowsConsoleHelper::Get()->GetConsoleHandle(),
        destStr,
        destStrLen,
        nullptr,
        nullptr
    );
#endif
}

void WindowsNativeConsole::WriteLine(const char* format, ...)
{
#ifndef TGON_DISABLE_CONSOLE
    wchar_t utf16Str[256];
    bool succeed = string::ConvertUTF8ToUTF16(format, reinterpret_cast<char*>(&utf16Str[0])) != -1;
    if (succeed)
    {
        va_list vaList;
        va_start(vaList, format);

        wchar_t destStr[256];
        auto destStrLen = wvsprintfW(destStr, utf16Str, vaList);

        destStr[destStrLen++] = L'\n';
        destStr[destStrLen] = L'\0';

        ::WriteConsoleW(
            WindowsConsoleHelper::Get()->GetConsoleHandle(),
            destStr,
            destStrLen,
            nullptr,
            nullptr
        );
    }
#endif
}

void WindowsNativeConsole::WriteLine(const wchar_t* format, ...)
{
#ifndef TGON_DISABLE_CONSOLE
    va_list vaList;
    va_start(vaList, format);

    wchar_t destStr[256];
    auto destStrLen = wvsprintfW(destStr, format, vaList);

    destStr[destStrLen++] = L'\n';
    destStr[destStrLen] = L'\0';

    ::WriteConsoleW(
        WindowsConsoleHelper::Get()->GetConsoleHandle(),
        destStr,
        destStrLen,
        nullptr,
        nullptr
    );
#endif
}

WindowsNativeConsole* WindowsNativeConsole::Get() noexcept
{
    static WindowsNativeConsole instance;
    return &instance;
}

} /* namespace platform */
} /* namespace tgon */