#include "PrecompiledHeader.h"

#include <sstream>
#include <array>
#if TGON_SUPPORT_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

#include "String/Encoding.h"
#include "Diagnostics/Debug.h"

#include "../Window.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

TGON_API void ConvertWindowStyleToNative(const WindowStyle& windowStyle, DWORD* rawWindowStyle, DWORD* rawExtendedWindowStyle)
{
	*rawExtendedWindowStyle = 0;
	*rawWindowStyle = 0;

	// Create a normal window style.
    {
        *rawWindowStyle |= WS_VISIBLE;
        
        if (windowStyle.resizeable)
        {
	    	*rawWindowStyle |= WS_THICKFRAME;
        }

        if (!windowStyle.hasCaption)
        {
            *rawWindowStyle |= WS_POPUP;
        }
        else
        {
            *rawWindowStyle |= WS_OVERLAPPED;
            *rawWindowStyle |= WS_CAPTION;
        }

        if (windowStyle.enableSystemButton)
        {
            *rawWindowStyle |= WS_SYSMENU;
            *rawWindowStyle |= WS_MINIMIZEBOX;
            *rawWindowStyle |= WS_MAXIMIZEBOX;
        }
    }

    // Create a extended window style.
    {
        if (windowStyle.topMost)
        {
            *rawExtendedWindowStyle |= WS_EX_TOPMOST;
        }
    }
}

/**
 * @brief                       Creates a window through given arguments.
 * @param [in] windowStyle		The window style information.
 * @param [in] instanceHandle	The handle of process instance.
 * @param [in] className		The name for class which stores window attributes.
 * @param [in] extraParam		The extra data to store in the window.
 */
HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className = L"TGON", void* extraParam = nullptr)
{
    // Convert the WindowStyle to the native window style.
    DWORD rawWindowStyle, rawExtendedWindowStyle;
    ConvertWindowStyleToNative(windowStyle, &rawWindowStyle, &rawExtendedWindowStyle);

    IPoint windowPos {static_cast<int>(windowStyle.x), static_cast<int>(windowStyle.y)};
    if (windowStyle.showMiddle)
    {
        // Set the window position to middle of the screen.
        windowPos.x = (GetSystemMetrics(SM_CXSCREEN) - windowStyle.width) / 2;
        windowPos.y = (GetSystemMetrics(SM_CYSCREEN) - windowStyle.height) / 2;
    }

    auto utf16Title = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(windowStyle.title.data()), windowStyle.title.size() + 1);

    // Convert the client size to window size.
    RECT windowSize {0, 0, windowStyle.width, windowStyle.height};
    AdjustWindowRect(&windowSize, rawWindowStyle, FALSE);

	HWND wndHandle = ::CreateWindowExW(
        rawExtendedWindowStyle,
        className,
        reinterpret_cast<LPCWSTR>(utf16Title.data()),
        rawWindowStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        windowPos.x,
        windowPos.y,
        windowSize.right - windowSize.left,
        windowSize.bottom - windowSize.top,
        nullptr,
        nullptr,
        instanceHandle,
        extraParam
	);

    if (wndHandle == nullptr)
    {
        std::stringstream ss;
        ss << "Failed to invoke CreateWindowExW. (Code: " << GetLastError() << ")";

        Debug::WriteLine(ss.str());
    }

    return wndHandle;
}

WindowsWindow::WindowsWindow(HWND wndHandle) noexcept :
    m_wndHandle(wndHandle)
{
    this->SetUserData(this);
}

WindowsWindow::WindowsWindow(WindowsWindow&& rhs) noexcept :
    m_wndHandle(rhs.m_wndHandle)
{
    rhs.m_wndHandle = nullptr;
}

bool Window::operator==(const Window& rhs) const noexcept
{
    return m_wndHandle == rhs.m_wndHandle;
}

bool Window::operator!=(const Window& rhs) const noexcept
{
    return m_wndHandle != rhs.m_wndHandle;
}

WindowsWindow& WindowsWindow::operator=(WindowsWindow&& rhs) noexcept
{
    m_wndHandle = rhs.m_wndHandle;
    
    rhs.m_wndHandle = nullptr;

    return *this;
}

void WindowsWindow::SetRawWindowStyle(DWORD rawWindowStyle)
{
    SetWindowLongPtrW(m_wndHandle, GWL_STYLE, rawWindowStyle);
}

void WindowsWindow::SetRawWindowStyleEx(DWORD rawWindowStyleEx)
{
    SetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE, rawWindowStyleEx);
}

LONG_PTR WindowsWindow::GetRawWindowStyle() const
{
    return GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
}

LONG_PTR WindowsWindow::GetRawWindowStyleEx() const
{
    return GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);
}

LRESULT WindowsWindow::OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto downcastedMe = reinterpret_cast<Window*>(this);

    switch (msg)
    {
    case WM_CREATE:
        break;

    case WM_SYSCOMMAND:
    {
        switch (wParam)
        {
        case SC_MINIMIZE:
            {
                if (downcastedMe->OnMinimize != nullptr)
                {
                    downcastedMe->OnMinimize();
                }
            }
            break;

        case SC_MAXIMIZE:
            {
                if (downcastedMe->OnMaximize != nullptr)
                {
                    downcastedMe->OnMaximize();
                }
            }
            break;
        }
    }
    break;

    case WM_SETFOCUS:
        {
            if (downcastedMe->OnGetFocus != nullptr)
            {
                downcastedMe->OnGetFocus();
            }
        }
        break;

    case WM_KILLFOCUS:
        {
            if (downcastedMe->OnLoseFocus != nullptr)
            {
                downcastedMe->OnLoseFocus();
            }
        }
        break;

    case WM_MOVE:
        {
            if (downcastedMe->OnMove != nullptr)
            {
                downcastedMe->OnMove(static_cast<int32_t>(LOWORD(lParam)), static_cast<int32_t>(HIWORD(lParam)));
            }
        }
        break;

    case WM_SIZE:
        {
            if (downcastedMe->OnResize != nullptr)
            {
                downcastedMe->OnResize(static_cast<int32_t>(LOWORD(lParam)), static_cast<int32_t>(HIWORD(lParam)));
            }
        }
        break;

    case WM_CLOSE:
        {
            if (downcastedMe->OnWillClose != nullptr)
            {
                downcastedMe->OnWillClose();
            }
        }
        break;

    case WM_DESTROY:
        {
            if (downcastedMe->OnDidClose != nullptr)
            {
                downcastedMe->OnDidClose();
            }

            downcastedMe->Close();

            // Destroy the message queue and quit the message loop.
            PostQuitMessage(0);
        }
        break;
    }

    return DefWindowProcW(wndHandle, msg, wParam, lParam);
}

void WindowsWindow::SetUserData(void* data)
{
    SetWindowLongPtrW(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
}

Window::Window(const WindowStyle& windowStyle) :
    WindowsWindow(CreateNativeWindow(windowStyle, GetModuleHandle(nullptr)))
{
}

void Window::BringToFront()
{
    // SetForegroundWindow, BringWindowToTop doesn't work as expected, therefore we will use a hack.
    bool isTopMost = this->IsTopMost();
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

    FlashWindowEx(&fwi);
}

void Window::GetPosition(int32_t* x, int32_t* y) const
{
    RECT rt;
    GetWindowRect(m_wndHandle, &rt);

    *x = rt.left;
    *y = rt.top;
}

void Window::GetExtent(int32_t* width, int32_t* height) const
{
    RECT rt;
    GetClientRect(m_wndHandle, &rt);

    *width = rt.right;
    *height = rt.bottom;
}

int32_t Window::GetTitle(char* destTitle, int32_t destTitleBufferLen) const
{
    auto utf16TitleLen = GetWindowTextW(m_wndHandle, &g_tempUtf16Buffer[0], 256);
    if (utf16TitleLen == 0)
    {
        return -1;
    }

    auto utf8TitleBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16TitleLen * 2), reinterpret_cast<std::byte*>(destTitle), destTitleBufferLen);
    if (utf8TitleBytes == -1)
    {
        return -1;
    }

    return utf8TitleBytes;
}

bool Window::IsResizable() const
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

bool Window::HasCaption() const
{
    return (this->GetRawWindowStyle() & WS_CAPTION) != 0;
}

bool Window::IsMaximized() const
{
    // todo : impl
    return false;
}

bool Window::IsMinimized() const
{
    // todo : impl
    return false;
}

bool Window::IsTopMost() const
{
    return (this->GetRawWindowStyleEx() & WS_EX_TOPMOST) != 0;
}

void* Window::GetNativeWindow() const
{
    return m_wndHandle;
}

void Window::Show()
{
    ShowWindow(m_wndHandle, SW_NORMAL);
}

void Window::Hide()
{
    ShowWindow(m_wndHandle, SW_HIDE);
}

void Window::Maximize()
{
    ShowWindow(m_wndHandle, SW_MAXIMIZE);
}

void Window::Minimize()
{
    ShowWindow(m_wndHandle, SW_MINIMIZE);
}

void Window::Close()
{
    if (m_wndHandle != nullptr)
    {
        DestroyWindow(m_wndHandle);
        m_wndHandle = nullptr;
    }
}

void Window::SetPosition(int32_t x, int32_t y)
{
    SetWindowPos(m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::SetContentSize(int32_t width, int32_t height)
{
    RECT rt{0, 0, width, height};

    DWORD rawWindowStyle = this->GetRawWindowStyle();
    DWORD rawExtendedWindowStyle = this->GetRawWindowStyleEx();

    AdjustWindowRectEx(&rt, rawWindowStyle, GetMenu(m_wndHandle) != nullptr, rawExtendedWindowStyle);

    if (rawWindowStyle & WS_VSCROLL)
    {
        rt.right += GetSystemMetrics(SM_CXVSCROLL);
    }

    if (rawWindowStyle & WS_HSCROLL)
    {
        rt.bottom += GetSystemMetrics(SM_CYVSCROLL);
    }

    SetWindowPos(m_wndHandle, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::SetTitle(const std::string_view& title)
{
    auto utf16TitleBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(title.data()), static_cast<int32_t>(title.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16TitleBytes == -1)
    {
        return;
    }


    SetWindowTextW(m_wndHandle, reinterpret_cast<LPCWSTR>(&g_tempUtf16Buffer[0]));
}

void Window::SetTopMost(bool setTopMost)
{
    SetWindowPos(m_wndHandle, setTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void Window::SetTransparency(float transparency)
{
    DWORD rawExtendedWindowStyle = this->GetRawWindowStyleEx();
    if ((rawExtendedWindowStyle & WS_EX_LAYERED) == false)
    {
        this->SetRawWindowStyleEx(rawExtendedWindowStyle | WS_EX_LAYERED);
    }

    SetLayeredWindowAttributes(m_wndHandle, 0, static_cast<BYTE>(transparency * 255.0f), LWA_ALPHA);
}

float Window::GetTransparency() const
{
    BYTE transparency;
    GetLayeredWindowAttributes(m_wndHandle, nullptr, &transparency, nullptr);

    return static_cast<float>(transparency) / 255.0f;
}

//void Window::SetWindowTransparencyPerPixel(const Color4f& pixel, float opacity)
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

} /* namespace tgon */
