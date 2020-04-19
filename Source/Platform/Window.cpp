#include "PrecompiledHeader.h"

#include <array>

#include "Window.h"

namespace tg
{

Window::Window(const WindowStyle& windowStyle) :
    PlatformWindow(windowStyle)
{
}

Window::~Window()
{
    this->Close();
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

}
