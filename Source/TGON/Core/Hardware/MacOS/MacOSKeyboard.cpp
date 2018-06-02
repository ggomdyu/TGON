#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "Keyboard.h"

namespace tgon
{
    
Keyboard::Keyboard(gainput::InputDeviceKeyboard* keyboardDevice) noexcept :
    m_keyboardDevice(keyboardDevice)
{
    assert(keyboardDevice != nullptr && "keyboardDevice can't be nullptr.");
}
    
bool Keyboard::IsKeyDown(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    if (m_keyboardDevice->GetBoolPrevious(castedKeyCode) == false &&
        m_keyboardDevice->GetBool(castedKeyCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool Keyboard::IsKeyUp(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    if (m_keyboardDevice->GetBoolPrevious(castedKeyCode) &&
        m_keyboardDevice->GetBool(castedKeyCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
