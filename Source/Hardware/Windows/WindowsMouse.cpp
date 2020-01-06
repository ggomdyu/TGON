#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "../Mouse.h"

namespace tgon
{

WindowsMouse::WindowsMouse(gainput::InputDeviceMouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}

const gainput::InputDeviceMouse* WindowsMouse::GetNativeMouse() const noexcept
{
    return m_nativeMouse;
}

gainput::InputDeviceMouse* WindowsMouse::GetNativeMouse() noexcept
{
    return m_nativeMouse;
}

Mouse::Mouse(InputManager& inputManager) :
    WindowsMouse(inputManager.GetPlatformDependency().CreateNativeMouse())
{
}

void Mouse::Update()
{
}
    
void Mouse::GetPosition(int32_t* x, int32_t* y)
{
}

bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    
    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) == false &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    
    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    
    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
