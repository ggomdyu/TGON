/**
 * @filename    InputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

#include "Mouse.h"
#include "Keyboard.h"
#include "Gamepad.h"

namespace tgon
{

class InputManager :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, InputManager)
{
public:
    TGON_RUNTIME_OBJECT(InputManager)

/* @section Public constructor */
public:
    using SuperType::SuperType;

/* @section Public destructor */
public:
    virtual ~InputManager() override = default;

/* @section Public method */
public:
    std::unique_ptr<Mouse> CreateMouse();
    std::unique_ptr<Keyboard> CreateKeyboard();
    std::unique_ptr<Gamepad> CreateGamepad();
};

} /* namespace tgon */
