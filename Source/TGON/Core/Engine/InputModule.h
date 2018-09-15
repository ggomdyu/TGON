/**
 * @file    InputModule.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>

#include "IModule.h"
#include "InputMode.h"

#include "Core/Hardware/InputManager.h"

namespace tgon
{
    
class Keyboard;
class Mouse;
class Gamepad;

class TGON_API InputModule :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(InputModule);
    
/**@section Public constructor */
public:
    InputModule(const InputMode& inputMode, Window& inputTarget);

/**@section Public method */
public:
    /**@brief   Updates the module. */
    virtual void Update() override;
    
    /**@brief   Gets the mouse device. */
    const std::unique_ptr<Mouse>& GetMouse() const noexcept;
    
    /**@brief   Gets the keyboard device. */
    const std::unique_ptr<Keyboard>& GetKeyboard() const noexcept;

    /**@brief   Gets the gamepad device. */
    const std::unique_ptr<Gamepad>& GetGamepad() const noexcept;

/**@section Private variable */
public:
    InputManager m_inputManager;

    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    std::unique_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
