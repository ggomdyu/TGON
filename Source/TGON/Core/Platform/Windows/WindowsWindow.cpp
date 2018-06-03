#include "PrecompiledHeader.h"

#include <cassert>
#include <Windows.h>
#if TGON_SUPPORT_DWMAPI && TGON_USING_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

#include "Core/String/Encoding.h"

#include "../Config.h"
#include "../Window.h"
#include "../Generic/GenericWindowType.h"

#include "WindowsWindowUtility.h"

namespace tgon
{

WindowsWindow::WindowsWindow(const WindowStyle& wndStyle) :
    m_wndHandle(CreateNativeWindow(wndStyle, GetModuleHandle(nullptr), L"TGON")),
    m_isDwmCompositionEnabled(false)
{
    assert(m_wndHandle != nullptr);
    
    // Store pointer to the window to WindowsWindow local extra memory.
    // It will be used to notify that the message event occured. 
    this->SetUserData(this);
}

WindowsWindow::WindowsWindow(WindowsWindow&& rhs) noexcept :
    m_wndHandle(rhs.m_wndHandle),
    m_isDwmCompositionEnabled(rhs.m_isDwmCompositionEnabled)
{
    rhs.m_wndHandle = nullptr;
    rhs.m_isDwmCompositionEnabled = false;
}

WindowsWindow& WindowsWindow::operator=(WindowsWindow&& rhs) noexcept
{
    if (this == &rhs)
    {
        return *this;
    }

    this->Close();

    GenericWindow::operator=(std::move(rhs));

    m_wndHandle = rhs.m_wndHandle;
    m_isDwmCompositionEnabled = rhs.m_isDwmCompositionEnabled;
    
    rhs.m_wndHandle = nullptr;
    rhs.m_isDwmCompositionEnabled = false;

    return *this;
}

WindowsWindow::~WindowsWindow()
{
    this->Close();
}

void WindowsWindow::BringToFront()
{
    // SetForegroundWindow, BringWindowToTop APIs are not working exactly.
    // The codes below are the hack way to reach it.
    bool isTopMost = this->IsTopMost();
    this->SetTopMost(true);
    this->SetTopMost(isTopMost);
}

void WindowsWindow::Flash()
{
    FLASHWINFO fwi {0};
    fwi.cbSize = sizeof(FLASHWINFO);
    fwi.dwFlags = FLASHW_CAPTION;
    fwi.dwTimeout = 0;
    fwi.hwnd = m_wndHandle;
    fwi.uCount = 1;

    ::FlashWindowEx(&fwi);
}

void WindowsWindow::GetPosition(int32_t* x, int32_t* y) const
{
    ::RECT rt;
    ::GetWindowRect(m_wndHandle, &rt);

    *x = rt.left;
    *y = rt.top;
}

void WindowsWindow::GetSize(int32_t* width, int32_t* height) const
{
    ::RECT rt;
    ::GetClientRect(m_wndHandle, &rt);

    *width = rt.right;
    *height = rt.bottom;
}

void WindowsWindow::GetTitle(char* destStr) const
{
    wchar_t utf16Title[256] {};
    int utf16TitleLen = ::GetWindowTextW(m_wndHandle, utf16Title, 256);

    UTF16LE::Convert<UTF8>(reinterpret_cast<const char*>(utf16Title), utf16TitleLen, destStr, 256);
}

bool WindowsWindow::IsResizable() const
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

bool WindowsWindow::HasCaption() const
{
    DWORD normalStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
    return (normalStyle & WS_CAPTION) != 0;
}

bool WindowsWindow::IsMaximized() const
{
    // todo : impl
    return false;
}

bool WindowsWindow::IsMinimized() const
{
    // todo : impl
    return false;
}

bool WindowsWindow::IsTopMost() const
{
    DWORD extendedStyle = GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);
    return (extendedStyle & WS_EX_TOPMOST) != 0;
}

const void* WindowsWindow::GetNativeWindow() const
{
    return m_wndHandle;
}

void WindowsWindow::Show()
{
    ::ShowWindow(m_wndHandle, SW_NORMAL);
}

void WindowsWindow::Hide()
{
    ::ShowWindow(m_wndHandle, SW_HIDE);
}

void WindowsWindow::Maximize()
{
    ::ShowWindow(m_wndHandle, SW_MAXIMIZE);
}

void WindowsWindow::Minimize()
{
    ::ShowWindow(m_wndHandle, SW_MINIMIZE);
}

void WindowsWindow::Close()
{
    ::DestroyWindow(m_wndHandle);
    m_isClosed = true;
}

void WindowsWindow::SetPosition(int32_t x, int32_t y)
{
    ::SetWindowPos(m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowsWindow::SetSize(int32_t width, int32_t height)
{
    ::RECT rt{0, 0, width, height};

    ::DWORD normalStyle = GetWindowLong(m_wndHandle, GWL_STYLE);
    ::DWORD extendedStyle = GetWindowLong(m_wndHandle, GWL_EXSTYLE);

    ::AdjustWindowRectEx(&rt, normalStyle, ::GetMenu(m_wndHandle) != nullptr, extendedStyle);

    if (normalStyle & WS_VSCROLL)
    {
        rt.right += GetSystemMetrics(SM_CXVSCROLL);
    }

    if (normalStyle & WS_HSCROLL)
    {
        rt.bottom += GetSystemMetrics(SM_CYVSCROLL);
    }

    ::SetWindowPos(m_wndHandle, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);
}

void WindowsWindow::SetTitle(const char* captionTitle)
{
    assert(captionTitle != nullptr);

    char utf16Title[512] {};
    bool succeed = UTF8::Convert<UTF16LE>(reinterpret_cast<const char*>(captionTitle), std::strlen(captionTitle), utf16Title, 512) != -1;
    if (succeed)
    {
        ::SetWindowTextW(m_wndHandle, reinterpret_cast<LPCWSTR>(utf16Title));
    }
}

void WindowsWindow::SetTopMost(bool setTopMost)
{
    ::SetWindowPos(m_wndHandle, setTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void WindowsWindow::SetTransparency(float transparency)
{
    ::SetLayeredWindowAttributes(m_wndHandle, 0, static_cast<BYTE>(transparency * 255.0f), LWA_ALPHA);
}

float WindowsWindow::GetTransparency() const
{
    BYTE transparency;
    ::GetLayeredWindowAttributes(m_wndHandle, nullptr, &transparency, nullptr);

    return transparency / 255.0f;
}

//void WindowsWindow::SetWindowTransparencyPerPixel(const Color4f& pixel, float opacity)
//{
//#if TGON_USING_DWMAPI
//    BOOL isCompoEnabled = FALSE;
//    DwmIsCompositionEnabled(&isCompoEnabled);
//    
//    if (isCompoEnabled == TRUE)
//    {
//        MARGINS margins {-1, -1, -1, -1};
//        DwmExtendFrameIntoClientArea(m_wndHandle, &margins);
//    }
//#endif
//}

LRESULT WindowsWindow::OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam)
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
            if (OnWindowDidClose != nullptr)
            {
                OnWindowDidClose();
            }

            this->Close();
            
            // Destroy the message queue and quit message loop.
            ::PostQuitMessage(0);
        }
        break;
    }

    return DefWindowProcW(wndHandle, msg, wParam, lParam);
}

void WindowsWindow::SetUserData(void* data)
{
    SetWindowLongPtrW(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG>(data));
}

} /* namespace tgon */