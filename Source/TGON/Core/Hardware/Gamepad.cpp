#include "PrecompiledHeader.h"

#include "Gamepad.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif
#include "InputManager.h"

namespace tgon
{

Gamepad::Gamepad(InputManager& inputManager) :
    m_gamepadImpl(std::make_unique<GamepadImpl>(inputManager.GetImpl()))
{
}
    
Gamepad::~Gamepad() = default;

void Gamepad::Update()
{
    m_gamepadImpl->Update();
}

void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_gamepadImpl->Vibrate(leftMotor, rightMotor);
}

bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    return m_gamepadImpl->IsButtonDown(buttonNumber);
}

bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    return m_gamepadImpl->IsButtonHold(buttonNumber);
}

bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    return m_gamepadImpl->IsButtonUp(buttonNumber);
}

const GamepadImpl& Gamepad::GetImpl() const noexcept
{
    return *m_gamepadImpl;
}

GamepadImpl& Gamepad::GetImpl() noexcept
{
    return *m_gamepadImpl;
}

} /* namespace tgon */
