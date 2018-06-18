/**
 * @file    MacOSKeyboard.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDeviceKeyboard;
    
} /* namespace gainput */

namespace tgon
{
    
enum class KeyCode;
class InputManagerImpl;
    
class TGON_API KeyboardImpl final
{
/* @section Public constructor */
public:
    explicit KeyboardImpl(InputManagerImpl* inputManagerImpl);
    
/* @section Public method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const gainput::InputDeviceKeyboard* GetKeyboardDevice() const noexcept;
    gainput::InputDeviceKeyboard* GetKeyboardDevice() noexcept;
    
/* @section Private variable */
private:
    gainput::InputDeviceKeyboard* m_keyboardDevice;
};

} /* namespace tgon */
