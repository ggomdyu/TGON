/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

namespace tgon
{

class Mouse;
class Keyboard;
class Gamepad;

class TGON_API InputManager final :
    private PlatformInputManager
{
/**@section Constructor */
public:
    using PlatformInputManager::PlatformInputManager;
    
/**@section Method */
public:
    std::unique_ptr<Mouse> CreateMouse();
    std::unique_ptr<Keyboard> CreateKeyboard();
    std::unique_ptr<Gamepad> CreateGamepad();

    using PlatformInputManager::Update;
};

} /* namespace tgon */
