#include "PrecompiledHeader.h"

#include "Window.h"

namespace tgon
{

Window::Window() :
    m_windowImpl(this)
{
}

Window::Window(const WindowStyle& windowStyle) :
    m_windowImpl(this, windowStyle)
{
}

Window::~Window() = default;

void Window::Show()
{
    m_windowImpl.Show();
}

void Window::Hide()
{
    m_windowImpl.Hide();
}

void Window::Close()
{
    m_windowImpl.Close();
}

void Window::Maximize()
{
    m_windowImpl.Maximize();
}

void Window::Minimize()
{
    m_windowImpl.Minimize();
}

void Window::BringToFront()
{
    m_windowImpl.BringToFront();
}

void Window::SetPosition(int32_t x, int32_t y)
{
    m_windowImpl.SetPosition(x, y);
}

void Window::SetSize(int32_t width, int32_t height)
{
    m_windowImpl.SetSize(width, height);
}

void Window::SetTitle(const char* title)
{
    m_windowImpl.SetTitle(title);
}

void Window::SetTopMost(bool setTopMost)
{
    m_windowImpl.SetTopMost(setTopMost);
}

void Window::SetTransparency(float transparency)
{
    m_windowImpl.SetTransparency(transparency);
}

void Window::GetPosition(int32_t* x, int32_t* y) const
{
    m_windowImpl.GetPosition(x, y);
}

void Window::GetSize(int32_t* width, int32_t* height) const
{
    m_windowImpl.GetSize(width, height);
}

void Window::GetTitle(char* destStr) const
{
    m_windowImpl.GetTitle(destStr);
}

I32Point Window::GetPosition() const
{
    I32Point::ValueType x, y;
    m_windowImpl.GetPosition(&x, &y);

    return {x, y};
}

I32Extent2D Window::GetSize() const
{
    I32Point::ValueType width, height;
    m_windowImpl.GetSize(&width, &height);

    return {width, height};
}

float Window::GetTransparency() const
{
    return m_windowImpl.GetTransparency();
}

void* Window::GetNativeWindow() const
{
    return m_windowImpl.GetNativeWindow();
}

bool Window::HasCaption() const
{
    return m_windowImpl.HasCaption();
}

bool Window::IsResizable() const
{
    return m_windowImpl.IsResizable();
}

bool Window::IsMaximized() const
{
    return m_windowImpl.IsMaximized();
}

bool Window::IsMinimized() const
{
    return m_windowImpl.IsMinimized();
}

bool Window::IsTopMost() const
{
    return m_windowImpl.IsTopMost();
}

const WindowImpl& Window::GetImpl() const noexcept
{
    return m_windowImpl;
}

WindowImpl& Window::GetImpl() noexcept
{
    return m_windowImpl;
}

} /* namespace tgon */
