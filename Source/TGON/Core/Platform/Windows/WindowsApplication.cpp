#include "PrecompiledHeader.pch"

#include <Windows.h>

#include "Core/String/Encoding.h"
#include "Core/Utility/Algorithm.h"

#include "../Window.h"
#include "../Generic/GenericWindowType.h"
#include "../Generic/GenericApplicationType.h"

#include "WindowsApplication.h"

namespace tgon
{
namespace
{

UINT ConvertMessageBoxIconTypeToNative(MessageBoxIconType messageBoxIconType) noexcept
{
    static constexpr const UINT nativeMessageBoxIconTypeTable[] =
    {
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };

    return nativeMessageBoxIconTypeTable[UnderlyingCast(messageBoxIconType)];
}

/* @brief   Register default WNDCLASS to window class table. */
bool RegisterWindowClass()
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

} /* namespace*/

WindowsApplication::WindowsApplication(const WindowStyle& windowStyle) :
    GenericApplication([&]()
    {
        RegisterWindowClass();
        return std::make_shared<Window>(windowStyle);
    } ())
{
}

void WindowsApplication::MessageLoop()
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
            this->OnUpdate();
        }
    }

    this->OnWillTerminate();
}

void WindowsApplication::ShowMessageBox(const char* title, const char* message, MessageBoxIconType messageBoxType) const
{
    wchar_t utf16Message[1024];
    UTF8::Convert<UTF16LE>(message, std::strlen(message), reinterpret_cast<char*>(utf16Message), std::extent<decltype(utf16Message)>::value);

    wchar_t utf16Title[256];
    UTF8::Convert<UTF16LE>(title, std::strlen(title), reinterpret_cast<char*>(utf16Title), std::extent<decltype(utf16Title)>::value);

    ::MessageBoxW(nullptr, utf16Message, utf16Title, ConvertMessageBoxIconTypeToNative(messageBoxType) | MB_OK);
}

LRESULT CALLBACK WindowsApplication::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
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

} /* namespace tgon */