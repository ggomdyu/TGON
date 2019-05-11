#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "Core/Algorithm.h"
#include "Hardware/Keyboard.h"

#include "MacOSKeyboard.h"
#include "MacOSKeyboardType.h"

namespace tgon
{
    
MacOSKeyboard::MacOSKeyboard(gainput::InputDeviceKeyboard* nativeKeyboard) :
    m_nativeKeyboard(nativeKeyboard)
{
}
    
void MacOSKeyboard::Update()
{
}
    
bool MacOSKeyboard::IsKeyDown(KeyCode keyCode) const
{
    auto castedKeyCode = UnderlyingCast(keyCode);
    if (m_nativeKeyboard->GetBoolPrevious(castedKeyCode) == false &&
        m_nativeKeyboard->GetBool(castedKeyCode))
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
    if (m_nativeKeyboard->GetBoolPrevious(castedKeyCode) &&
        m_nativeKeyboard->GetBool(castedKeyCode))
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
    if (m_nativeKeyboard->GetBoolPrevious(castedKeyCode) &&
        m_nativeKeyboard->GetBool(castedKeyCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
gainput::InputDeviceKeyboard* MacOSKeyboard::GetNativeKeyboard() noexcept
{
    return m_nativeKeyboard;
}

const gainput::InputDeviceKeyboard* MacOSKeyboard::GetNativeKeyboard() const noexcept
{
    return m_nativeKeyboard;
}

} /* namespace tgon */
