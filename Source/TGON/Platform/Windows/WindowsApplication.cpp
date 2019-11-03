#include "PrecompiledHeader.h"

#include "Text/Encoding.h"

#include "../Application.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

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
    const wchar_t* utf16Message = &g_tempUtf16Buffer[0];
    auto utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(title.data()), static_cast<int32_t>(title.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    auto utf16MessageLen = utf16MessageBytes / 2;
    const wchar_t* utf16Title = &g_tempUtf16Buffer[utf16MessageLen + 1];
    auto utf16TitleBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(&message[0]), static_cast<int32_t>(message.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[utf16MessageLen + 1]), static_cast<int32_t>(g_tempUtf16Buffer.size() - (utf16MessageBytes + sizeof(wchar_t))));
    if (utf16TitleBytes == -1)
    {
        return;
    }

    ::MessageBoxW(nullptr, utf16Title, utf16Message, ConvertMessageBoxIconToNative(messageBoxIcon) | MB_OK);
}

} /* namespace tgon */
