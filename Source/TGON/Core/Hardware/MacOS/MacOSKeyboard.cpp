#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "MacOSKeyboard.h"

namespace tgon
{
    
MacOSKeyboard::MacOSKeyboard(gainput::InputDeviceKeyboard* keyboardDevice) noexcept :
    m_keyboardDevice(keyboardDevice)
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
    
MacOSKeyboard* MacOSKeyboard::GetPlatformService()
{
    return this;
}

const MacOSKeyboard* MacOSKeyboard::GetPlatformService() const
{
    return this;
}
    
gainput::InputDeviceKeyboard* MacOSKeyboard::GetKeyboardDevice()
{
    return m_keyboardDevice;
}

const gainput::InputDeviceKeyboard* MacOSKeyboard::GetKeyboardDevice() const
{
    return m_keyboardDevice;
}

} /* namespace tgon */
