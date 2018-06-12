/**
 * @filename    WindowsKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#include "WindowsKeyboardFwd.h"

namespace tgon
{

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
    const OIS::Keyboard* GetKeyboardDevice() const noexcept;
    OIS::Keyboard* GetKeyboardDevice() noexcept;
    
/* @section Private variable */
private:
    OIS::Keyboard* m_keyboardDevice;
    char m_prevKeyStates[256];
};

} /* namespace tgon */
