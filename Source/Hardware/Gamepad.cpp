#include "PrecompiledHeader.h"

#include "Gamepad.h"

namespace tgon
{

Gamepad::Gamepad(gainput::InputDevicePad* nativeGamepad) noexcept :
    m_nativeGamepad(nativeGamepad)
{
}

Gamepad::Gamepad(Gamepad&& rhs) noexcept :
    m_nativeGamepad(rhs.m_nativeGamepad)
{
}

Gamepad& tgon::Gamepad::operator=(Gamepad&& rhs) noexcept
{
    m_nativeGamepad = rhs.m_nativeGamepad;

    rhs.m_nativeGamepad = nullptr;

    return *this;
}

void Gamepad::Update()
{
}
    
void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    m_nativeGamepad->Vibrate(leftMotor, rightMotor);
}
    
bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    return false;
}
    
bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    return false;
}
    
bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    return false;
}

} /* namespace tgon */
