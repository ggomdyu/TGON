/**
 * @filename    MacOSKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "MacOSKeyboardType.h"

namespace tgon
{
    
class MacOSKeyboard :
    public GenericKeyboard
{
/* @section Public constructor */
public:
    explicit MacOSKeyboard(void* keyboardDevice) noexcept;

/* @section Public destructor */
public:
    virtual ~MacOSKeyboard() override = default;
    
/* @section Public method */
public:
    virtual void Update() final override;
    virtual bool IsKeyDown(KeyCode keyCode) const final override;
    virtual bool IsKeyHold(KeyCode keyCode) const final override;
    virtual bool IsKeyUp(KeyCode keyCode) const final override;

/* @section Private variable */
private:
    gainput::InputDeviceKeyboard* m_keyboardDevice;
};
    
using Keyboard = MacOSKeyboard;

} /* namespace tgon */
