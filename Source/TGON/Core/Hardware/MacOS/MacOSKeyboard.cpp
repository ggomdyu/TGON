#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "Core/Utility/Algorithm.h"
#include "Core/Hardware/Keyboard.h"

#include "MacOSKeyboard.h"
#include "MacOSKeyboardType.h"
#include "MacOSInputManager.h"

namespace tgon
{
    
KeyboardImpl::KeyboardImpl(InputManagerImpl& platformInputManager) :
    m_keyboardDevice(platformInputManager.CreateKeyboardDevice())
{
}
    
void KeyboardImpl::Update()
{
}
    
bool KeyboardImpl::IsKeyDown(KeyCode keyCode) const
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
    
bool KeyboardImpl::IsKeyHold(KeyCode keyCode) const
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
    
bool KeyboardImpl::IsKeyUp(KeyCode keyCode) const
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
    
gainput::InputDeviceKeyboard* KeyboardImpl::GetKeyboardDevice() noexcept
{
    return m_keyboardDevice;
}

const gainput::InputDeviceKeyboard* KeyboardImpl::GetKeyboardDevice() const noexcept
{
    return m_keyboardDevice;
}

} /* namespace tgon */
