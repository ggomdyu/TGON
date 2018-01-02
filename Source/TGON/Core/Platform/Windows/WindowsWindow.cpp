#include "PrecompiledHeader.pch"

#include "WindowsWindowUtility.h"

#include "../Window.h"
#include "../WindowType.h"
#include "../Config.h"

#include "Core/String/Encoding.h"

#include <Windows.h>
#include <cassert>
#if TGON_SUPPORT_DWMAPI && TGON_USING_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#pragma comment(lib, "icudt.lib")
#pragma comment(lib, "icutud.lib")
#pragma comment(lib, "icuind.lib")
#pragma comment(lib, "icuucd.lib")

namespace tgon
{
namespace platform
{

Window::Window(const WindowStyle& wndStyle) :
    m_wndHandle(CreateNativeWindow(wndStyle, GetModuleHandle(nullptr), L"TGON")),
    m_isClosed(false),
    m_isDwmCompositionEnabled(false)
{
    assert(m_wndHandle != nullptr && "Failed to create window.");
    
    // Store pointer to the window to Window local extra memory.
    // It will be used to notify that the message event occured. 
    this->SetUserData(this);
}

Window::Window(Window&& rhs) noexcept :
    m_wndHandle(rhs.m_wndHandle),
    m_isClosed(rhs.m_isClosed),
    m_isDwmCompositionEnabled(rhs.m_isDwmCompositionEnabled)
{
    rhs.m_wndHandle = nullptr;
    rhs.m_isDwmCompositionEnabled = false;
}

Window& Window::operator=(Window&& rhs) noexcept
{
    new (this) Window(std::move(rhs));

    return *this;
}

Window::~Window()
{
    ::DestroyWindow(m_wndHandle);
}

void Window::Initialize(const WindowStyle& windowStyle)
{
    new (this) Window(windowStyle);
}

void Window::BringToFront()
{
    // SetForegroundWindow, BringWindowToTop APIs are not working exactly.
    // The codes below are the hack way to reach it.
    bool isTopMost = IsTopMost();
    this->SetTopMost(true);
    this->SetTopMost(isTopMost);
}

void Window::Flash()
{
    FLASHWINFO fwi {0};
    fwi.cbSize = sizeof(FLASHWINFO);
    fwi.dwFlags = FLASHW_CAPTION;
    fwi.dwTimeout = 0;
    fwi.hwnd = m_wndHandle;
    fwi.uCount = 1;

    ::FlashWindowEx(&fwi);
}

void Window::GetPosition(int32_t* x, int32_t* y) const
{
    ::RECT rt;
    ::GetWindowRect(m_wndHandle, &rt);

    *x = rt.left;
    *y = rt.top;
}

void Window::GetSize(int32_t* width, int32_t* height) const
{
    ::RECT rt;
    ::GetClientRect(m_wndHandle, &rt);

    *width = rt.right;
    *height = rt.bottom;
}

void Window::GetTitle(char* destStr) const
{
    wchar_t title[256] {};
    int titleLen = ::GetWindowTextW(m_wndHandle, title, 256);

#if 1
    icu::UnicodeString unicodeStr(title);

    std::string str;
    unicodeStr.toUTF8String(str);

    memcpy(destStr, str.data(), str.length() + 1);
#endif
}

bool Window::IsResizable() const
{
    DWORD normalStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
    if ((normalStyle & WS_THICKFRAME) != 0)
    {
        return true;
    }

	DWORD extendedStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);
    if ((extendedStyle & WS_EX_DLGMODALFRAME) != 0)
    {
        return true;
    }

    return false;
}

bool Window::HasCaption() const
{
    DWORD normalStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
    return (normalStyle & WS_CAPTION) != 0;
}

bool Window::IsMaximized() const
{
    // todo : impl
    return false;
}

bool Window::IsTopMost() const
{
    DWORD extendedStyle = GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);
    return (extendedStyle & WS_EX_TOPMOST) != 0;
}

void* Window::GetNativeWindow() noexcept
{
    return m_wndHandle;
}

void Window::Show()
{
    ::ShowWindow(m_wndHandle, SW_NORMAL);
}

void Window::Hide()
{
    ::ShowWindow(m_wndHandle, SW_HIDE);
}

void Window::Maximize()
{
    ::ShowWindow(m_wndHandle, SW_MAXIMIZE);
}

void Window::Minimize()
{
    ::ShowWindow(m_wndHandle, SW_MINIMIZE);
}

void Window::Close()
{
    ::PostQuitMessage(0);
    m_isClosed = true;
}

void Window::SetPosition(int32_t x, int32_t y)
{
    ::SetWindowPos(m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE);
}

void Window::SetSize(int32_t width, int32_t height)
{
    ::SetWindowPos(m_wndHandle, nullptr, 0, 0, width, height, SWP_NOMOVE);
}

void Window::SetTitle(const char* captionTitle)
{
    wchar_t utf16Caption[512] {};

    bool succeed = string::ConvertUTF8ToUTF16(captionTitle, reinterpret_cast<char*>(utf16Caption)) != -1;
    if (succeed)
    {
        ::SetWindowTextW(m_wndHandle, utf16Caption);
    }
}

void Window::SetTopMost(bool setTopMost)
{
    ::SetWindowPos(m_wndHandle, setTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void Window::SetWindowTransparency(float opacity)
{
    ::SetLayeredWindowAttributes(m_wndHandle, 0, static_cast<BYTE>(opacity * 255.0f), LWA_ALPHA);
}

//void Window::SetWindowTransparencyPerPixel(const math::Color4f& pixel, float opacity)
//{
//    BOOL isCompoEnabled = FALSE;
//    DwmIsCompositionEnabled(&isCompoEnabled);
//    
//    if (isCompoEnabled == TRUE)
//    {
//        MARGINS margins {-1, -1, -1, -1};
//        DwmExtendFrameIntoClientArea(m_wndHandle, &margins);
//    }
//}

LRESULT Window::OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        break;

    case WM_SYSCOMMAND:
        {
            switch(wParam)
            {
            case SC_MINIMIZE:
                {
                    if (OnWindowMinimize != nullptr)
                    {
                        OnWindowMinimize();
                    }
                }
                break;
            case SC_MAXIMIZE:
                {
                    if (OnWindowMaximize != nullptr)
                    {
                        OnWindowMaximize();
                    }
                }
                break;
            }
        }
        break;

    case WM_SETFOCUS:
        {
            if (OnWindowGetFocus != nullptr)
            {
                OnWindowGetFocus();
            }
        }
        break;

    case WM_KILLFOCUS:
        {
            if (OnWindowLoseFocus != nullptr)
            {
                OnWindowLoseFocus();
            }
        }
        break;

    case WM_MOVE:
        {
            if (OnWindowMove != nullptr)
            {
                OnWindowMove(static_cast<int32_t>(LOWORD(lParam)), static_cast<int32_t>(HIWORD(lParam)));
            }
        }
        break;

    case WM_SIZE:
        {
            if (OnWindowResize != nullptr)
            {
                OnWindowResize(static_cast<int32_t>(LOWORD(lParam)), static_cast<int32_t>(HIWORD(lParam)));
            }   
        }
        break;

    case WM_CLOSE:
        {
            if (OnWindowWillClose != nullptr)
            {
                OnWindowWillClose();
            }
        }
        break;

    case WM_DESTROY:
        {
            m_isClosed = true;

            if (OnWindowDidClose != nullptr)
            {
                OnWindowDidClose();
            }

            // Destroy the message queue and quit loop.
            ::PostQuitMessage(0);
        }
        break;
    }

    return DefWindowProc(wndHandle, msg, wParam, lParam);
}

void Window::SetUserData(void* data)
{
    SetWindowLongPtr(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG>(data));
}

} /* namespace platform */
} /* namespace tgon */