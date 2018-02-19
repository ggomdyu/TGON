#include "PrecompiledHeader.pch"

#include "WindowsApplication.h"

#include "../Window.h"
#include "../Generic/GenericWindowType.h"
#include "../Generic/GenericApplicationType.h"

#include <Windows.h>

namespace tgon
{
namespace core
{
namespace
{

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
    static constexpr const LONG nativeMessageBoxIconTypeTable[2] =
    {
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };

    // todo: 나중에 파라미터로 utf8을 받게한 뒤 utf16으로 변환해서, MessageBoxW함수로 처리하도록 해야할 듯.
    // 일단 icu 라이브러리 붙이는게 시급함.
    ::MessageBoxA(nullptr, message, title, nativeMessageBoxIconTypeTable[static_cast<int>(messageBoxType)] | MB_OK);
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

} /* namespace core */
} /* namespace tgon */