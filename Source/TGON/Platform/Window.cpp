#include "PrecompiledHeader.h"

#include <array>

#include "Window.h"

namespace tgon
{

extern thread_local std::array<char, 16384> g_tempUtf8Buffer;

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

I32Point Window::GetPosition() const
{
    I32Point::ValueType x, y;
    this->GetPosition(&x, &y);

    return {x, y};
}

I32Extent2D Window::GetWindowSize() const
{
    I32Point::ValueType width, height;
    this->GetWindowSize(&width, &height);

    return {width, height};
}

I32Extent2D Window::GetClientSize() const
{
    I32Point::ValueType width, height;
    this->GetClientSize(&width, &height);

    return {width, height};
}

std::string Window::GetTitle() const
{
    int32_t utf8TitleLen = this->GetTitle(&g_tempUtf8Buffer[0], static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(&g_tempUtf8Buffer[0], utf8TitleLen);
}

} /* namespace tgon */
