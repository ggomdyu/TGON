#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSGamepad.h"
#include "MacOSGamepadType.h"

namespace tgon
{

MacOSGamepad::MacOSGamepad(gainput::InputDevicePad* nativeGamepad) :
    m_nativeGamepad(nativeGamepad)
{
}
    
void MacOSGamepad::Update()
{
}
    
void MacOSGamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_nativeGamepad->Vibrate(leftMotor, rightMotor);
}
    
bool MacOSGamepad::IsButtonDown(int32_t buttonNumber) const
{
    return false;
}
    
bool MacOSGamepad::IsButtonHold(int32_t buttonNumber) const
{
    return false;
}
    
bool MacOSGamepad::IsButtonUp(int32_t buttonNumber) const
{
    return false;
}
    
const gainput::InputDevicePad* MacOSGamepad::GetNativeGamepad() const noexcept
{
    return m_nativeGamepad;
}

gainput::InputDevicePad* MacOSGamepad::GetNativeGamepad() noexcept
{
    return m_nativeGamepad;
}

} /* namespace tgon */
