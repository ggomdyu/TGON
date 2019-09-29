#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "../Keyboard.h"

namespace tgon
{
    
MacOSKeyboard::MacOSKeyboard(gainput::InputDeviceKeyboard* nativeKeyboard) :
    m_nativeKeyboard(nativeKeyboard)
{
}

gainput::InputDeviceKeyboard* MacOSKeyboard::GetNativeKeyboard() noexcept
{
    return m_nativeKeyboard;
}

const gainput::InputDeviceKeyboard* MacOSKeyboard::GetNativeKeyboard() const noexcept
{
    return m_nativeKeyboard;
}
    
Keyboard::Keyboard(InputManager& inputManager) :
    MacOSKeyboard(inputManager.GetPlatformDependency().CreateNativeKeyboard())
{
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
