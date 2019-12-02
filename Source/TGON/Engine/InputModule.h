/**
 * @file    InputModule.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>

#include "Hardware/InputManager.h"
#include "Hardware/Keyboard.h"
#include "Hardware/Mouse.h"
#include "Hardware/Gamepad.h"

#include "Module.h"

namespace tgon
{
    
struct InputMode
{
/**@section Variable */
    bool isUseKeyboard = true;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

class InputModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(InputModule)
    
/**@section Constructor */
public:
    explicit InputModule(const Window& inputTarget, const InputMode& inputMode = {});

/**@section Method */
public:
    std::shared_ptr<Mouse> GetMouse() noexcept;
    std::shared_ptr<const Mouse> GetMouse() const noexcept;
    std::shared_ptr<Keyboard> GetKeyboard() noexcept;
    std::shared_ptr<const Keyboard> GetKeyboard() const noexcept;
    std::shared_ptr<Gamepad> GetGamepad() noexcept;
    std::shared_ptr<const Gamepad> GetGamepad() const noexcept;
    void Update() override;
    
/**@section Variable */
public:
    InputManager m_inputManager;
    std::shared_ptr<Keyboard> m_keyboard;
    std::shared_ptr<Mouse> m_mouse;
    std::shared_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
