#include "PrecompiledHeader.h"

#include "Mouse.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif
#include "InputManager.h"

namespace tgon
{
    
Mouse::Mouse(InputManager& inputManager) :
    m_platformMouse(inputManager.GetPlatformDependency())
{
}
    
Mouse::~Mouse() = default;
    
void Mouse::Update()
{
    m_platformMouse.Update();
}

void Mouse::GetPosition(int32_t* x, int32_t* y)
{
    PlatformMouse::GetPosition(x, y);
}

I32Point Mouse::GetPosition()
{
    I32Point pt;
    PlatformMouse::GetPosition(&pt.x, &pt.y);

    return pt;
}
    
bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    return m_platformMouse.IsMouseDown(mouseCode);
}

bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    return m_platformMouse.IsMouseHold(mouseCode);
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    return m_platformMouse.IsMouseUp(mouseCode);
}

const PlatformMouse& Mouse::GetPlatformDependency() const noexcept
{
    return m_platformMouse;
}

PlatformMouse& Mouse::GetPlatformDependency() noexcept
{
    return m_platformMouse;
}

} /* namespace tgon */
