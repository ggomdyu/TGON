#include "PrecompiledHeader.h"

#import <AppKit/AppKit.h>

#include "Core/Utility/Algorithm.h"

#include "MacOSGamepad.h"

namespace tgon
{

MacOSGamepad::MacOSGamepad(gainput::InputDevicePad* gamepadDevice) noexcept :
    m_gamepadDevice(gamepadDevice)
{
    assert(gamepadDevice != nullptr && "gamepadDevice can't be nullptr.");
}
    
void MacOSGamepad::Update()
{
}
    
void MacOSGamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_gamepadDevice->Vibrate(leftMotor, rightMotor);
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

} /* namespace tgon */
