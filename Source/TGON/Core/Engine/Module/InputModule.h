/**
 * @file    InputModule.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>

#include "Core/Hardware/InputManager.h"

#include "IModule.h"

namespace tgon
{
    
class Keyboard;
class Mouse;
class Gamepad;

struct InputMode final
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

constexpr InputMode::InputMode(bool isUseKeyboard, bool isUseMouse, bool isUseGamepad) noexcept :
    isUseKeyboard(isUseKeyboard),
    isUseMouse(isUseMouse),
    isUseGamepad(isUseGamepad)
{
}
    
class TGON_API InputModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(InputModule);
    
/**@section Public constructor */
public:
    InputModule(const std::shared_ptr<Window>& inputTarget, const InputMode& inputMode);

/**@section Public destructor */
public:
    virtual ~InputModule() final override;

/**@section Public method */
public:
    virtual void Update() final override;
    
    const std::unique_ptr<Mouse>& GetMouse() const noexcept;
    const std::unique_ptr<Keyboard>& GetKeyboard() const noexcept;
    const std::unique_ptr<Gamepad>& GetGamepad() const noexcept;

/**@section Private variable */
public:
    InputManager m_inputManager;

    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    std::unique_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
