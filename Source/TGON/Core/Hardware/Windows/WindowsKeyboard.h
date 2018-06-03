/**
 * @filename    WindowsKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "WindowsKeyboardType.h"

namespace tgon
{
    
class WindowsKeyboard :
    public GenericKeyboard
{
/* @section Public constructor */
public:
    explicit WindowsKeyboard(OIS::Keyboard* keyboardDevice) noexcept;
    
/* @section Public destructor */
public:
    virtual ~WindowsKeyboard() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    virtual bool IsKeyDown(KeyCode keyCode) const override;
    virtual bool IsKeyHold(KeyCode keyCode) const override;
    virtual bool IsKeyUp(KeyCode keyCode) const override;

/* @section Private variable */
private:
    OIS::Keyboard* m_keyboardDevice;
    char m_prevKeyStates[256];
};

using Keyboard = WindowsKeyboard;

} /* namespace tgon */
