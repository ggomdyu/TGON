#include "PrecompiledHeader.pch"

#include "WindowsApplication.h"
#include "WindowsWindow.h"


#include <cstdint>
#include <crtdbg.h>
#include <Windows.h>

#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "Engine/Engine.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace tgon
{
namespace platform
{
namespace windows
{

WindowsApplication::WindowsApplication(HINSTANCE instanceHandle) :
    m_instanceHandle(instanceHandle)
{
}

void WindowsApplication::Initialize(HINSTANCE instanceHandle)
{
}

WindowsApplication* WindowsApplication::Get()
{
    static WindowsApplication instance;
    return &instance;
}

LRESULT CALLBACK WindowsApplication::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*auto extraMemAsWindow = reinterpret_cast<windows::WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (extraMemAsWindow)
    {
        return extraMemAsWindow->OnHandleMessage(wndHandle, message, wParam, lParam);
    }*/

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

HINSTANCE WindowsApplication::GetInstanceHandle() const noexcept
{
    return m_instanceHandle;
}

//void WindowsApplication::GetLanguage(char* destBuffer, std::size_t bufferLength)
//{
//    ::GetLocaleInfoA(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, destBuffer, bufferLength);
//}

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */