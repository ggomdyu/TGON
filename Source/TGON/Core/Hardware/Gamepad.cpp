#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif

#include "Gamepad.h"
#include "InputManager.h"

namespace tgon
{

Gamepad::Gamepad(InputManager* inputManager) :
    m_impl(std::make_unique<GamepadImpl>(inputManager->GetImpl()))
{
}
    
Gamepad::~Gamepad() = default;

void Gamepad::Update()
{
    m_impl->Update();
}

void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_impl->Vibrate(leftMotor, rightMotor);
}

bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    return m_impl->IsButtonDown(buttonNumber);
}

bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    return m_impl->IsButtonHold(buttonNumber);
}

bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    return m_impl->IsButtonUp(buttonNumber);
}

const GamepadImpl* Gamepad::GetImpl() const noexcept
{
    return m_impl.get();
}

GamepadImpl* Gamepad::GetImpl() noexcept
{
    return m_impl.get();
}

} /* namespace tgon */
