#include "PrecompiledHeader.h"

#include <Windows.h>

#include "Core/String/Encoding.h"

#include "../Application.h"
#include "../Window.h"
#include "../Generic/GenericWindowType.h"
#include "../Generic/GenericApplicationType.h"

#include "WindowsApplicationUtility.h"

namespace tgon
{

WindowsApplication::WindowsApplication() :
    GenericApplication()
{
    RegisterWindowClass();
}

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

void WindowsApplication::ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxType) const
{
    wchar_t utf16Message[1024] {};
    UTF8::Convert<UTF16LE>(message, std::strlen(message), reinterpret_cast<char*>(utf16Message), std::extent<decltype(utf16Message)>::value);

    wchar_t utf16Title[256] {};
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