#include "PrecompiledHeader.h"

#include <StackWalker.h>

#include "Platform/Config.h"
#include "String/Encoding.h"

#include "WindowsApplication.h"
#include "WindowsWindow.h"

namespace tgon
{

constexpr UINT ConvertMessageBoxIconToNative(MessageBoxIcon messageBoxIcon) noexcept
{
    constexpr UINT nativeMessageBoxIcons[] = {
        -1,
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };
    return nativeMessageBoxIcons[static_cast<int>(messageBoxIcon)];
}

WindowsApplication::WindowsApplication() :
    m_doCrashReport(false)
{
    RegisterWindowClass();
}

void WindowsApplication::ShowMessageBox(const std::string_view& title, const std::string_view& message, MessageBoxIcon messageBoxIcon) const
{
    wchar_t utf16Message[1024] {};
    UTF8::ConvertTo<UTF16LE>(message, reinterpret_cast<char*>(utf16Message), std::extent<decltype(utf16Message)>::value);

    wchar_t utf16Title[256] {};
    UTF8::ConvertTo<UTF16LE>(title, reinterpret_cast<char*>(utf16Title), std::extent<decltype(utf16Title)>::value);

    ::MessageBoxW(nullptr, utf16Message, utf16Title, ConvertMessageBoxIconToNative(messageBoxIcon) | MB_OK);
}

void WindowsApplication::EnableCrashHandler()
{
    SetUnhandledExceptionFilter([](EXCEPTION_POINTERS* exceptionPointers) -> LONG
    {
        StackWalker stackWalker;
        stackWalker.ShowCallstack(::GetCurrentThread(), exceptionPointers->ContextRecord, 0, 0);

        MessageBox(nullptr, L"HI", L"HI", MB_OK);
        
        return EXCEPTION_CONTINUE_SEARCH;
    });

    //PreventSetUnhandledExceptionFilter();
}

LRESULT CALLBACK WindowsApplication::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (window)
    {
        return window->OnHandleMessage(wndHandle, message, wParam, lParam);
    }

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

void WindowsApplication::Terminate()
{
    ::PostQuitMessage(0);
}

bool WindowsApplication::RegisterWindowClass()
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = sizeof(void*);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpfnWndProc = WindowsApplication::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace tgon */
