#include "PrecompiledHeader.h"

#include "Gamepad.h"

namespace tgon
{

Gamepad::Gamepad(InputManager& inputManager) :
    m_gamepadImpl(inputManager.GetImpl())
{
}
    
Gamepad::~Gamepad() = default;

void Gamepad::Update()
{
    m_gamepadImpl.Update();
}

void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_gamepadImpl.Vibrate(leftMotor, rightMotor);
}

bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    return m_gamepadImpl.IsButtonDown(buttonNumber);
}

bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    return m_gamepadImpl.IsButtonHold(buttonNumber);
}

bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    return m_gamepadImpl.IsButtonUp(buttonNumber);
}

const GamepadImpl& Gamepad::GetImpl() const noexcept
{
    return m_gamepadImpl;
}

GamepadImpl& Gamepad::GetImpl() noexcept
{
    return m_gamepadImpl;
}

} /* namespace tgon */
