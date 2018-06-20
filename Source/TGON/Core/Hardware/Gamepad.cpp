#include "PrecompiledHeader.h"

#include "Gamepad.h"
#include "InputManager.h"

namespace tgon
{

Gamepad::Gamepad(InputManager& inputManager) :
    m_platformGamepad(inputManager.GetPlatformDependency())
{
}
    
Gamepad::~Gamepad() = default;

void Gamepad::Update()
{
    m_platformGamepad.Update();
}

void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_platformGamepad.Vibrate(leftMotor, rightMotor);
}

bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    return m_platformGamepad.IsButtonDown(buttonNumber);
}

bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    return m_platformGamepad.IsButtonHold(buttonNumber);
}

bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    return m_platformGamepad.IsButtonUp(buttonNumber);
}

const PlatformGamepad& Gamepad::GetPlatformDependency() const noexcept
{
    return m_platformGamepad;
}

PlatformGamepad& Gamepad::GetPlatformDependency() noexcept
{
    return m_platformGamepad;
}

} /* namespace tgon */
