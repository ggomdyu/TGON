#include "PrecompiledHeader.pch"
#include "../Window.h"
#include "../WindowType.h"

#include <Windows.h>
#include <cassert>
#ifdef TGON_SUPPORT_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

#include "Core/String/Encoding.h"

#include "WindowsWindowUtility.h"

namespace tgon
{
namespace platform
{

Window::Window(const WindowStyle& wndStyle) :
    m_wndHandle(CreateNativeWindow(wndStyle, GetModuleHandle(nullptr), L"TGON")),
    m_isClosed(false)
{
    assert(m_wndHandle != nullptr && "Failed to create window.");

    // Store this instance's pointer into window's user data storage.
    SetWindowLongPtrW(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

Window::Window(Window&& rhs) noexcept :
    m_wndHandle(rhs.m_wndHandle),
    m_isClosed(rhs.m_isClosed)
{
    rhs.m_wndHandle = nullptr;
}

Window& Window::operator=(Window&& rhs) noexcept
{
    m_wndHandle = rhs.m_wndHandle;
    m_isClosed = rhs.m_isClosed;

    rhs.m_wndHandle = nullptr;

    return *this;
}

Window::~Window()
{
    DestroyWindow(m_wndHandle);
}

void Window::Initialize(const WindowStyle& windowStyle)
{
    new (this) Window(windowStyle);
}

void Window::BringToFront()
{
	// 테스트 필요
    ::SetForegroundWindow(m_wndHandle);
    ::BringWindowToTop(m_wndHandle);
}

void Window::Flash()
{
    ::FLASHWINFO fwi{ 0 };
    fwi.cbSize = sizeof(::FLASHWINFO);
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
    //std::size_t captionTextLength = GetWindowTextLengthW(m_wndHandle);
    
    //::GetWindowTextW(m_wndHandle, destStr, captionTextLength);
    // utf16 -> utf8;
}

bool Window::IsResizable() const
{
    // Todo: WS_EX_DLGMODALFRAME에 대해서 테스트 필요

    ::DWORD style = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
	::DWORD extendedStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);

    return ((style & WS_THICKFRAME) != 0) || ((extendedStyle & WS_EX_DLGMODALFRAME) != 0);
}

bool Window::HasCaption() const
{
    // 테스트 필요
    DWORD style = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
    return (style & WS_CAPTION) != 0;
}

bool Window::IsMaximized() const
{
    // todo : impl
    return false;
}

bool Window::IsTopMost() const
{
    return false;
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
    wchar_t utf16Caption[256] {};

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

//void Window::AdditionalInit(const WindowStyle& wndStyle)
//{
//    if (wndStyle.supportWindowTransparency)
//    {
//        SetLayeredWindowAttributes(m_wndHandle, NULL, 255, LWA_ALPHA);
//    }
//
//#ifdef TGON_SUPPORT_DWMAPI
//    if (wndStyle.supportPerPixelTransparency)
//    {
//        BOOL isCompoEnabled = FALSE;
//        DwmIsCompositionEnabled(&isCompoEnabled);
//
//        if (isCompoEnabled == TRUE)
//        {
//            MARGINS margins{ -1, -1, -1, -1 };
//            DwmExtendFrameIntoClientArea(m_wndHandle, &margins);
//        }
//    }
//#endif
//}
LRESULT Window::OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        break;

    case WM_SETFOCUS:
        {
            this->OnGetFocus();
        }
        break;

    case WM_KILLFOCUS:
        {
            this->OnLoseFocus();
        }
        break;

    case WM_MOVE:
        {
            this->OnMove((std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam));
        }
        break;

    case WM_SIZE:
        {
			this->OnResize((std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam));
        }
        break;

    case WM_DESTROY:
        {
            this->Close();
        }
        break;
    }

    return DefWindowProc(wndHandle, msg, wParam, lParam);
}

} /* namespace platform */
} /* namespace tgon */