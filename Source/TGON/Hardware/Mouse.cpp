#include "PrecompiledHeader.h"

#include "Mouse.h"

namespace tgon
{

I32Point Mouse::GetPosition()
{
    I32Point pt;
    Mouse::GetPosition(&pt.x, &pt.y);

    return pt;
}

PlatformMouse& Mouse::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformMouse& Mouse::GetPlatformDependency() const noexcept
{
    return *this;
}

}
