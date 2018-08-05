/**
 * @file    Keyboard.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif

#include "InputManager.h"

namespace tgon
{

class TGON_API Keyboard final
{
/* @section Public constructor */
public:
    explicit Keyboard(InputManager& inputManager);
    
/* @section Public destructor */
public:
    ~Keyboard();
    
/* @section Public method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const KeyboardImpl& GetImpl() const noexcept;
    KeyboardImpl& GetImpl() noexcept;
    
/* @section Private variable */
private:
    std::unique_ptr<KeyboardImpl> m_keyboardImpl;
};
    
} /* namespace tgon */
