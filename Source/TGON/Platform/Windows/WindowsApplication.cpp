#include "PrecompiledHeader.h"

#include "String/Encoding.h"

#include "../Application.h"

namespace tgon
{
namespace
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

}

WindowsApplication::WindowsApplication()
{
    RegisterDefaultWindowClass();
}

/**@brief   Register default WNDCLASS to window class table. */
bool WindowsApplication::RegisterDefaultWindowClass()
{
    WNDCLASSEXW wcex {};
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = sizeof(void*);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandleW(nullptr);
    wcex.lpfnWndProc = [](HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
        if (window)
        {
            return window->OnHandleMessage(wndHandle, message, wParam, lParam);
        }

        return DefWindowProc(wndHandle, message, wParam, lParam);
    };

    return RegisterClassExW(&wcex) != 0;
}

void Application::Terminate()
{
    PostQuitMessage(0);
}

void Application::MessageLoop()
{
    MSG msg {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            ::DispatchMessageW(&msg);
        }
        else
        {
            m_engine->Update();
        }
    }
}

void Application::ShowMessageBox(const std::string_view& title, const std::string_view& message, MessageBoxIcon messageBoxIcon)
{
    wchar_t utf16Message[1024] {};
    UTF8::ConvertTo<UTF16LE>(message, reinterpret_cast<char*>(utf16Message), std::extent<decltype(utf16Message)>::value);

    wchar_t utf16Title[256] {};
    UTF8::ConvertTo<UTF16LE>(title, reinterpret_cast<char*>(utf16Title), std::extent<decltype(utf16Title)>::value);

    ::MessageBoxW(nullptr, utf16Message, utf16Title, ConvertMessageBoxIconToNative(messageBoxIcon) | MB_OK);
}

}
