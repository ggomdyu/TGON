/**
 * @file    Keyboard.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif

#include "InputManager.h"

namespace tgon
{

class TGON_API Keyboard final :
    private PlatformKeyboard
{
/**@section Constructor */
public:
    explicit Keyboard(InputManager& inputManager);

/**@section Method */
public:
    PlatformKeyboard& GetPlatformDependency() noexcept;
    const PlatformKeyboard& GetPlatformDependency() const noexcept;
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
};
    
}
