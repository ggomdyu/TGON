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

} /* namespace tgon */
