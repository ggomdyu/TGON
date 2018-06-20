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

namespace tgon
{

class InputManager;
enum class KeyCode;

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
    const PlatformKeyboard& GetPlatformDependency() const noexcept;
    PlatformKeyboard& GetPlatformDependency() noexcept;
    
/* @section Private variable */
private:
    PlatformKeyboard m_platformKeyboard;
};
    
} /* namespace tgon */
