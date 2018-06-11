#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSWindow.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidWindow.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSWindow.h"
#endif

#include "Window.h"
#include "WindowType.h"

namespace tgon
{

Window::Window() :
    m_impl(new WindowImpl(this))
{
}

Window::Window(const WindowStyle& windowStyle) :
    m_impl(new WindowImpl(this, windowStyle))
{
}

Window::Window(Window&& rhs) noexcept :
    m_impl(rhs.m_impl)
{
    rhs.m_impl = nullptr;
}

void Window::Show()
{
    m_impl->Show();
}

void Window::Hide()
{
    m_impl->Hide();
}

void Window::Close()
{
    m_impl->Close();
}

void Window::Maximize()
{
    m_impl->Maximize();
}

void Window::Minimize()
{
    m_impl->Minimize();
}

void Window::BringToFront()
{
    m_impl->BringToFront();
}

void Window::SetPosition(int32_t x, int32_t y)
{
    m_impl->SetPosition(x, y);
}

void Window::SetSize(int32_t width, int32_t height)
{
    m_impl->SetSize(width, height);
}

void Window::SetTitle(const char* title)
{
    m_impl->SetTitle(title);
}

void Window::SetTopMost(bool setTopMost)
{
    m_impl->SetTopMost(setTopMost);
}

void Window::SetTransparency(float transparency)
{
    m_impl->SetTransparency(transparency);
}

void Window::GetPosition(int32_t* x, int32_t* y) const
{
    m_impl->GetPosition(x, y);
}

void Window::GetSize(int32_t* width, int32_t* height) const
{
    m_impl->GetSize(width, height);
}

void Window::GetTitle(char* destStr) const
{
    m_impl->GetTitle(destStr);
}

I32Point Window::GetPosition() const
{
    I32Point::ValueType x, y;
    m_impl->GetPosition(&x, &y);

    return {x, y};
}

I32Extent2D Window::GetSize() const
{
    I32Point::ValueType width, height;
    m_impl->GetSize(&width, &height);

    return {width, height};
}

float Window::GetTransparency() const
{
    return m_impl->GetTransparency();
}

void* Window::GetNativeWindow()
{
    return m_impl->GetNativeWindow();
}

const void* Window::GetNativeWindow() const
{
    return m_impl->GetNativeWindow();
}

bool Window::HasCaption() const
{
    return m_impl->HasCaption();
}

bool Window::IsResizable() const
{
    return m_impl->IsResizable();
}

bool Window::IsMaximized() const
{
    return m_impl->IsMaximized();
}

bool Window::IsMinimized() const
{
    return m_impl->IsMinimized();
}

bool Window::IsTopMost() const
{
    return m_impl->IsTopMost();
}

} /* namespace tgon */
