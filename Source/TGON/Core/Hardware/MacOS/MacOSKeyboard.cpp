#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "MacOSKeyboard.h"

namespace tgon
{
    
MacOSKeyboard::MacOSKeyboard(void* keyboardDevice) noexcept :
    m_keyboardDevice(reinterpret_cast<gainput::InputDeviceKeyboard*>(keyboardDevice))
{
    assert(keyboardDevice != nullptr && "keyboardDevice can't be nullptr.");
}
    
void MacOSKeyboard::Update()
{
}
    
bool MacOSKeyboard::IsKeyDown(KeyCode keyCode) const
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
    
bool MacOSKeyboard::IsKeyHold(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    if (m_keyboardDevice->GetBoolPrevious(castedKeyCode) &&
        m_keyboardDevice->GetBool(castedKeyCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MacOSKeyboard::IsKeyUp(KeyCode keyCode) const
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
