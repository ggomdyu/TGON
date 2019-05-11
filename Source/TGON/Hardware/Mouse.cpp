#include "PrecompiledHeader.h"

#include "Mouse.h"

namespace tgon
{

I32Point Mouse::GetPosition()
{
    I32Point pt;
    PlatformMouse::GetPosition(&pt.x, &pt.y);

    return pt;
}
 
} /* namespace tgon */
