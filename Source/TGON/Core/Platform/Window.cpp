#include "PrecompiledHeader.h"

#include "Window.h"
#include "WindowType.h"

namespace tgon
{

Window::Window() :
    m_platformWindow(this)
{
}

Window::Window(const WindowStyle& windowStyle) :
    m_platformWindow(this, windowStyle)
{
}

Window::~Window() = default;

std::shared_ptr<Window> Window::Create()
{
    return std::shared_ptr<Window>(new Window());
}

std::shared_ptr<Window> Window::Create(const WindowStyle& windowStyle)
{
    return std::shared_ptr<Window>(new Window(windowStyle));
}

void Window::Show()
{
    m_platformWindow.Show();
}

void Window::Hide()
{
    m_platformWindow.Hide();
}

void Window::Close()
{
    m_platformWindow.Close();
}

void Window::Maximize()
{
    m_platformWindow.Maximize();
}

void Window::Minimize()
{
    m_platformWindow.Minimize();
}

void Window::BringToFront()
{
    m_platformWindow.BringToFront();
}

void Window::SetPosition(int32_t x, int32_t y)
{
    m_platformWindow.SetPosition(x, y);
}

void Window::SetSize(int32_t width, int32_t height)
{
    m_platformWindow.SetSize(width, height);
}

void Window::SetTitle(const char* title)
{
    m_platformWindow.SetTitle(title);
}

void Window::SetTopMost(bool setTopMost)
{
    m_platformWindow.SetTopMost(setTopMost);
}

void Window::SetTransparency(float transparency)
{
    m_platformWindow.SetTransparency(transparency);
}

void Window::GetPosition(int32_t* x, int32_t* y) const
{
    m_platformWindow.GetPosition(x, y);
}

void Window::GetSize(int32_t* width, int32_t* height) const
{
    m_platformWindow.GetSize(width, height);
}

void Window::GetTitle(char* destStr) const
{
    m_platformWindow.GetTitle(destStr);
}

I32Point Window::GetPosition() const
{
    I32Point::ValueType x, y;
    m_platformWindow.GetPosition(&x, &y);

    return {x, y};
}

I32Extent2D Window::GetSize() const
{
    I32Point::ValueType width, height;
    m_platformWindow.GetSize(&width, &height);

    return {width, height};
}

float Window::GetTransparency() const
{
    return m_platformWindow.GetTransparency();
}

void* Window::GetNativeWindow()
{
    return m_platformWindow.GetNativeWindow();
}

const void* Window::GetNativeWindow() const
{
    return m_platformWindow.GetNativeWindow();
}

bool Window::HasCaption() const
{
    return m_platformWindow.HasCaption();
}

bool Window::IsResizable() const
{
    return m_platformWindow.IsResizable();
}

bool Window::IsMaximized() const
{
    return m_platformWindow.IsMaximized();
}

bool Window::IsMinimized() const
{
    return m_platformWindow.IsMinimized();
}

bool Window::IsTopMost() const
{
    return m_platformWindow.IsTopMost();
}

const PlatformWindow& Window::GetPlatformDependency() const noexcept
{
    return m_platformWindow;
}

PlatformWindow& Window::GetPlatformDependency() noexcept
{
    return m_platformWindow;
}

} /* namespace tgon */
