#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSGamepad.h"
#include "MacOSGamepadType.h"
#include "MacOSInputManager.h"

namespace tgon
{

MacOSGamepad::MacOSGamepad(MacOSInputManager& platformInputManager) :
    m_gamepadDevice(platformInputManager.CreateGamepadDevice())
{
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
    
const gainput::InputDevicePad* MacOSGamepad::GetGamepadDevice() const noexcept
{
    return m_gamepadDevice;
}

gainput::InputDevicePad* MacOSGamepad::GetGamepadDevice() noexcept
{
    return m_gamepadDevice;
}

} /* namespace tgon */
