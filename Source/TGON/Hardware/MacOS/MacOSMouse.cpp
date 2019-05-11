#import "PrecompiledHeader.h"

#import <gainput/gainput.h>
#import <AppKit/AppKit.h>

#import "Core/Algorithm.h"

#import "MacOSMouse.h"
#import "MacOSMouseType.h"

namespace tgon
{

MacOSMouse::MacOSMouse(gainput::InputDeviceMouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}
    
void MacOSMouse::Update()
{
}
    
void MacOSMouse::GetPosition(int32_t* x, int32_t* y)
{
    NSPoint pt = [NSEvent mouseLocation];
    pt.y = [NSScreen mainScreen].frame.size.height - pt.y;
    
    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
}

bool MacOSMouse::IsMouseDown(MouseCode mouseCode) const
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
    
bool MacOSMouse::IsMouseHold(MouseCode mouseCode) const
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

bool MacOSMouse::IsMouseUp(MouseCode mouseCode) const
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
    
const gainput::InputDeviceMouse* MacOSMouse::GetNativeMouse() const noexcept
{
    return m_nativeMouse;
}

gainput::InputDeviceMouse* MacOSMouse::GetNativeMouse() noexcept
{
    return m_nativeMouse;
}

} /* namespace tgon */
