#include "PrecompiledHeader.h"

#include "../Application.h"

namespace tg
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
    return nativeMessageBoxIcons[static_cast<int32_t>(messageBoxIcon)];
}

}

WindowsApplication::WindowsApplication()
{
    WindowsApplication::RegisterDefaultWindowClass();
}

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

void WindowsApplication::SetMessageHandler(MessageHandler messageHandler, void* messageHandlerParam)
{
    m_messageHandler = messageHandler;
    m_messageHandlerParam = messageHandlerParam;
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

            if (m_messageHandler != nullptr)
            {
                m_messageHandler(msg, m_messageHandlerParam);
            }
        }
        else
        {
            m_engine->Update();
        }
    }
}

void Application::ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon)
{
    wchar_t utf16Title[2048];
    auto utf16TitleLen = MultiByteToWideChar(CP_UTF8, 0, title, -1, utf16Title, std::extent_v<decltype(utf16Title)>);
    if (utf16TitleLen == 0)
    {
        return;
    }

    wchar_t utf16Message[2048];
    auto utf16MessageLen = MultiByteToWideChar(CP_UTF8, 0, message, -1, utf16Message, std::extent_v<decltype(utf16Message)>);
    if (utf16MessageLen == 0)
    {
        return;
    }

    ::MessageBoxW(nullptr, &utf16Message[0], &utf16Title[0], ConvertMessageBoxIconToNative(messageBoxIcon) | MB_OK);
}

}
