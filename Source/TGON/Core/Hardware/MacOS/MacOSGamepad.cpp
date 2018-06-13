#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSGamepad.h"
#include "MacOSGamepadType.h"
#include "MacOSInputManager.h"

namespace tgon
{

GamepadImpl::GamepadImpl(InputManagerImpl* inputManagerImpl) :
    m_gamepadDevice(inputManagerImpl->CreateGamepadDevice())
{
}
    
void GamepadImpl::Update()
{
}
    
void GamepadImpl::Vibrate(float leftMotor, float rightMotor)
{
    m_gamepadDevice->Vibrate(leftMotor, rightMotor);
}
    
bool GamepadImpl::IsButtonDown(int32_t buttonNumber) const
{
    return false;
}
    
bool GamepadImpl::IsButtonHold(int32_t buttonNumber) const
{
    return false;
}
    
bool GamepadImpl::IsButtonUp(int32_t buttonNumber) const
{
    return false;
}
    
const gainput::InputDevicePad* GamepadImpl::GetGamepadDevice() const noexcept
{
    return m_gamepadDevice;
}

gainput::InputDevicePad* GamepadImpl::GetGamepadDevice() noexcept
{
    return m_gamepadDevice;
}

} /* namespace tgon */
