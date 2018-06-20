#import "PrecompiledHeader.h"

#import <gainput/gainput.h>
#import <AppKit/AppKit.h>

#import "Core/Utility/Algorithm.h"

#import "MacOSMouse.h"
#import "MacOSMouseType.h"
#import "MacOSInputManager.h"

namespace tgon
{

MouseImpl::MouseImpl(MacOSInputManager& platformInputManager) :
    m_mouseDevice(platformInputManager.CreateMouseDevice())
{
}
    
void MouseImpl::Update()
{
}
    
void MouseImpl::GetPosition(int32_t* x, int32_t* y) const
{
    NSPoint pt = [NSEvent mouseLocation];
    pt.y = [NSScreen mainScreen].frame.size.height - pt.y;
    
    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
}

//float MouseImpl::GetFloat(MouseCode mouseCode) const
//{
//    auto castedMouseCode = UnderlyingCast(mouseCode);
//    return m_mouseDevice->GetFloat(castedMouseCode);
//}
    
bool MouseImpl::IsMouseDown(MouseCode mouseCode) const
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
    
bool MouseImpl::IsMouseHold(MouseCode mouseCode) const
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

bool MouseImpl::IsMouseUp(MouseCode mouseCode) const
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
    
const gainput::InputDeviceMouse* MouseImpl::GetMouseDevice() const noexcept
{
    return m_mouseDevice;
}

gainput::InputDeviceMouse* MouseImpl::GetMouseDevice() noexcept
{
    return m_mouseDevice;
}

} /* namespace tgon */
