/**
 * @filename    InputModule.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <memory>

#include "Core/Object/Module/IModule.h"

#include "Core/Hardware/InputManager.h"
#include "Core/Hardware/Keyboard.h"
#include "Core/Hardware/Mouse.h"
#include "Core/Hardware/Gamepad.h"

namespace tgon
{

struct InputMode
{
/* @section Public constructor */
public:
    constexpr InputMode() noexcept = default;
    constexpr InputMode(bool isUseKeyboard, bool isUseMouse, bool isUseGamepad) noexcept;
    
/* @section Public variable */
public:
    bool isUseKeyboard = true;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

class TGON_API InputModule :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(InputModule);
    
/* @section Public constructor */
public:
    InputModule(const InputMode& inputMode, const std::shared_ptr<Window>& inputTarget);

/* @section Public method */
public:
    virtual void Update() override;
    
    const std::unique_ptr<Mouse>& GetMouse() const;
    const std::unique_ptr<Keyboard>& GetKeyboard() const;
    const std::unique_ptr<Gamepad>& GetGamepad() const;

/* @section Private variable */
public:
    InputManager m_inputManager;

    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    std::unique_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
