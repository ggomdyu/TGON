/**
 * @filename    MacOSKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#include "MacOSKeyboardType.h"
#include "MacOSKeyboardFwd.h"

namespace tgon
{
    
class TGON_API KeyboardImpl final
{
/* @section Public constructor */
public:
    explicit KeyboardImpl(InputManager* inputManager);
    
/* @section Public method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const gainput::InputDeviceKeyboard* GetKeyboardDevice() const;
    gainput::InputDeviceKeyboard* GetKeyboardDevice();
    
/* @section Private variable */
private:
    gainput::InputDeviceKeyboard* m_keyboardDevice;
};

} /* namespace tgon */
