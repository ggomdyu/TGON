/**
 * @filename    WindowsKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

namespace OIS
{

class Keyboard;

} /* namespace OIS */

namespace tgon
{

enum class KeyCode;
class InputManagerImpl;

class TGON_API KeyboardImpl final
{
/* @section Public constructor */
public:
    explicit KeyboardImpl(InputManagerImpl& platformInputManager);

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

using PlatformKeyboard = KeyboardImpl;

} /* namespace tgon */
