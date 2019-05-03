#include "PrecompiledHeader.h"

#include "Window.h"

namespace tgon
{

I32Point Window::GetPosition() const
{
    I32Point::ValueType x, y;
    this->GetPosition(&x, &y);

    return {x, y};
}

I32Extent2D Window::GetSize() const
{
    I32Point::ValueType width, height;
    this->GetSize(&width, &height);

    return {width, height};
}
    
PlatformWindow* Window::GetPlatformDependency() noexcept
{
    return this;
}

const PlatformWindow* Window::GetPlatformDependency() const noexcept
{
    return this;
}

} /* namespace tgon */
