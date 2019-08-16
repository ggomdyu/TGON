#import "PrecompiledHeader.h"

#import <AppKit/AppKit.h>

#import "Misc/Algorithm.h"

#import "../Mouse.h"

namespace tgon
{

MacOSMouse::MacOSMouse(gainput::InputDeviceMouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}

const gainput::InputDeviceMouse* MacOSMouse::GetNativeMouse() const noexcept
{
    return m_nativeMouse;
}

gainput::InputDeviceMouse* MacOSMouse::GetNativeMouse() noexcept
{
    return m_nativeMouse;
}

Mouse::Mouse(InputManager& inputManager) :
    MacOSMouse(inputManager.GetPlatformDependency().CreateNativeMouse())
{
}

void Mouse::Update()
{
}
    
void Mouse::GetPosition(int32_t* x, int32_t* y)
{
    NSPoint pt = [NSEvent mouseLocation];
    pt.y = [NSScreen mainScreen].frame.size.height - pt.y;
    
    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
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
