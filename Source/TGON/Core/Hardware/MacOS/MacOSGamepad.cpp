#include "PrecompiledHeader.h"

#import <AppKit/AppKit.h>

#include "Core/Utility/Algorithm.h"

#include "MacOSGamepad.h"

namespace tgon
{

MacOSGamepad::MacOSGamepad(void* gamepadDevice) noexcept :
    m_gamepadDevice(reinterpret_cast<gainput::InputDevicePad*>(gamepadDevice))
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

} /* namespace tgon */
