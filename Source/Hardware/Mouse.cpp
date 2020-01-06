#include "PrecompiledHeader.h"

#include "Mouse.h"

namespace tgon
{

I32Vector2 Mouse::GetPosition()
{
    I32Vector2 pt;
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

} /* namespace tgon */
