#include "PrecompiledHeader.h"

#include "Core/Algorithm.h"

#include "Keyboard.h"

namespace tgon
{
    
Keyboard::Keyboard(gainput::InputDeviceKeyboard* nativeKeyboard) noexcept :
    m_nativeKeyboard(nativeKeyboard)
{
}
    
Keyboard::Keyboard(Keyboard&& rhs) noexcept :
    m_nativeKeyboard(rhs.m_nativeKeyboard)
{
    rhs.m_nativeKeyboard = nullptr;
}

Keyboard& Keyboard::operator=(Keyboard&& rhs) noexcept
{
    m_nativeKeyboard = rhs.m_nativeKeyboard;

    rhs.m_nativeKeyboard = nullptr;

    return *this;
}

void Keyboard::Update()
{
}
    
bool Keyboard::IsKeyDown(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    return m_nativeKeyboard->GetBoolPrevious(castedKeyCode) == false && m_nativeKeyboard->GetBool(castedKeyCode);
}
    
bool Keyboard::IsKeyHold(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    return m_nativeKeyboard->GetBoolPrevious(castedKeyCode) && m_nativeKeyboard->GetBool(castedKeyCode);
}
    
bool Keyboard::IsKeyUp(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    return m_nativeKeyboard->GetBoolPrevious(castedKeyCode) && m_nativeKeyboard->GetBool(castedKeyCode) == false;
}
    
} /* namespace tgon */
