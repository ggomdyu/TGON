#include "PrecompiledHeader.h"

#include <type_traits>
#include <cassert>
#if TGON_SUPPORT_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

#include "Core/String/Encoding.h"

#include "WindowsWindow.h"
#include "WindowsWindowUtility.h"

namespace tgon
{

WindowsWindow::WindowsWindow(const WindowStyle& windowStyle) :
    m_wndHandle(WindowsWindowUtility::CreateNativeWindow(windowStyle, GetModuleHandle(nullptr), L"TGON")),
    m_isDwmCompositionEnabled(false)
{
    assert(m_wndHandle != nullptr);

    // Store pointer to the window to extra memory.
    // It will be used to notify that the message event occured. 
    this->SetUserData(this);
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

    UTF16LE::Convert<UTF8>(utf16Title, utf16TitleLen, destStr, 256);
}

bool WindowsWindow::IsResizable() const
{
    if ((this->GetRawWindowStyle() & WS_THICKFRAME) != 0)
    {
        return true;
    }

    if ((this->GetRawWindowStyleEx() & WS_EX_DLGMODALFRAME) != 0)
    {
        return true;
    }

    return false;
}

bool WindowsWindow::HasCaption() const
{
    return (this->GetRawWindowStyle() & WS_CAPTION) != 0;
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
    return (this->GetRawWindowStyleEx() & WS_EX_TOPMOST) != 0;
}

void WindowsWindow::SetRawWindowStyle(DWORD rawWindowStyle)
{
    SetWindowLongPtrW(m_wndHandle, GWL_STYLE, rawWindowStyle);
}

void WindowsWindow::SetRawWindowStyleEx(DWORD rawWindowStyleEx)
{
}

LONG_PTR WindowsWindow::GetRawWindowStyle() const
{
    return ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
}

LONG_PTR WindowsWindow::GetRawWindowStyleEx() const
{
    return ::GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);
}

void* WindowsWindow::GetNativeWindow() const
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
}

void WindowsWindow::SetPosition(int32_t x, int32_t y)
{
    ::SetWindowPos(m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowsWindow::SetSize(int32_t width, int32_t height)
{
    ::RECT rt{0, 0, width, height};

    ::DWORD rawWindowStyle = this->GetRawWindowStyle();
    ::DWORD rawExtendedWindowStyle = this->GetRawWindowStyleEx();

    ::AdjustWindowRectEx(&rt, rawWindowStyle, ::GetMenu(m_wndHandle) != nullptr, rawExtendedWindowStyle);

    if (rawWindowStyle & WS_VSCROLL)
    {
        rt.right += GetSystemMetrics(SM_CXVSCROLL);
    }

    if (rawWindowStyle & WS_HSCROLL)
    {
        rt.bottom += GetSystemMetrics(SM_CYVSCROLL);
    }

    ::SetWindowPos(m_wndHandle, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);
}

void WindowsWindow::SetTitle(const char* captionTitle)
{
    assert(captionTitle != nullptr);

    char utf16Title[512] {};
    bool isConvertSucceed = UTF8::Convert<UTF16LE>(captionTitle, std::strlen(captionTitle), utf16Title, std::extent_v<decltype(utf16Title)>);
    if (isConvertSucceed)
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
    DWORD rawExtendedWindowStyle = this->GetRawWindowStyleEx();
    if ((rawExtendedWindowStyle & WS_EX_LAYERED) == false)
    {
        this->SetRawWindowStyleEx(rawExtendedWindowStyle | WS_EX_LAYERED);
    }

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
    SetWindowLongPtrW(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
}

} /* namespace tgon */
