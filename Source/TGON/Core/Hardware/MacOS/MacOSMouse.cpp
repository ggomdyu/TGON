#include "PrecompiledHeader.h"

#import <AppKit/AppKit.h>

#include "Core/Utility/Algorithm.h"

#include "MacOSMouse.h"

namespace tgon
{

MacOSMouse::MacOSMouse(gainput::InputDeviceMouse* mouseDevice) noexcept :
    m_mouseDevice(mouseDevice)
{
    assert(mouseDevice != nullptr && "mouseDevice can't be nullptr.");
}
    
void MacOSMouse::Update()
{
}
    
void MacOSMouse::GetPosition(int32_t* x, int32_t* y) const
{
    NSPoint pt = [NSEvent mouseLocation];
    pt.y = [NSScreen mainScreen].frame.size.height - pt.y;
    
    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
}

float MacOSMouse::GetFloat(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    return m_mouseDevice->GetFloat(castedMouseCode);
}
    
bool MacOSMouse::IsMouseDown(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    if (m_mouseDevice->GetBoolPrevious(castedMouseCode) == false &&
        m_mouseDevice->GetBool(castedMouseCode))
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
    if (m_mouseDevice->GetBoolPrevious(castedMouseCode) &&
        m_mouseDevice->GetBool(castedMouseCode))
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
    if (m_mouseDevice->GetBoolPrevious(castedMouseCode) &&
        m_mouseDevice->GetBool(castedMouseCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
