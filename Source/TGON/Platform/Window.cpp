#include "PrecompiledHeader.h"

#include <array>

#include "Window.h"

namespace tgon
{

Window::~Window()
{
    this->Close();
}

Window::Window(Window&& rhs) noexcept :
    PlatformWindow(std::move(rhs)),
    OnMove(std::move(rhs.OnMove)),
    OnResize(std::move(rhs.OnResize)),
    OnMaximize(std::move(rhs.OnMaximize)),
    OnMinimize(std::move(rhs.OnMinimize)),
    OnEnterFullScreen(std::move(rhs.OnEnterFullScreen)),
    OnExitFullScreen(std::move(rhs.OnExitFullScreen)),
    OnWillClose(std::move(rhs.OnWillClose)),
    OnDidClose(std::move(rhs.OnDidClose)),
    OnGetFocus(std::move(rhs.OnGetFocus)),
    OnLoseFocus(std::move(rhs.OnLoseFocus))
{
}

Window& Window::operator=(Window&& rhs) noexcept
{
    PlatformWindow::operator=(std::move(rhs));

    OnMove = std::move(rhs.OnMove);
    OnResize = std::move(rhs.OnResize);
    OnMaximize = std::move(rhs.OnMaximize);
    OnMinimize = std::move(rhs.OnMinimize);
    OnEnterFullScreen = std::move(rhs.OnEnterFullScreen);
    OnExitFullScreen = std::move(rhs.OnExitFullScreen);
    OnWillClose = std::move(rhs.OnWillClose);
    OnDidClose = std::move(rhs.OnDidClose);
    OnGetFocus = std::move(rhs.OnGetFocus);
    OnLoseFocus = std::move(rhs.OnLoseFocus);

    return *this;
}

PlatformWindow& Window::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformWindow& Window::GetPlatformDependency() const noexcept
{
    return *this;
}

I32Vector2 Window::GetPosition() const
{
    int32_t x, y;
    this->GetPosition(&x, &y);
    return {x, y};
}

I32Extent2D Window::GetWindowSize() const
{
    int32_t width, height;
    this->GetWindowSize(&width, &height);
    return {width, height};
}

I32Extent2D Window::GetClientSize() const
{
    int32_t width, height;
    this->GetClientSize(&width, &height);
    return {width, height};
}

std::string Window::GetTitle() const
{
    std::array<char, 8192> str;
    int32_t titleLen = this->GetTitle(&str[0], static_cast<int32_t>(str.size()));
    return {&str[0], static_cast<size_t>(titleLen)};
}

} /* namespace tgon */
