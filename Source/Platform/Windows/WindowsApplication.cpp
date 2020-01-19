#include "PrecompiledHeader.h"

#include "Text/Encoding.h"

#include "../Application.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 16383> g_tempUtf16Buffer;

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

} /* namespace */

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
    gsl::span<wchar_t> utf16Title(&g_tempUtf16Buffer[0], 2048);
    int32_t utf16TitleBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&title[0]), static_cast<int32_t>(strlen(title)), reinterpret_cast<std::byte*>(&utf16Title[0]), static_cast<int32_t>(utf16Title.size()));
    if (utf16TitleBytes == -1)
    {
        return;
    }

    gsl::span<wchar_t> utf16Message(&g_tempUtf16Buffer[2048], g_tempUtf16Buffer.size() - 2048);
    int32_t utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&message[0]), static_cast<int32_t>(strlen(message)), reinterpret_cast<std::byte*>(&utf16Message[0]), static_cast<int32_t>(utf16Message.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    ::MessageBoxW(reinterpret_cast<HWND>(GetRootWindow()->GetNativeWindow()), &utf16Message[0], &utf16Title[0], ConvertMessageBoxIconToNative(messageBoxIcon) | MB_OK);
}

} /* namespace tgon */
