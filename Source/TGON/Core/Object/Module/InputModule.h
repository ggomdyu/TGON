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

namespace tgon
{

struct InputMode
{
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
    InputModule(const InputMode& inputMode, const std::shared_ptr<GenericWindow>& inputTargetWindow);

/* @section Public method */
public:
    virtual void Update() override;
    
    const std::unique_ptr<Mouse>& GetMouse() const;
    const std::unique_ptr<Keyboard>& GetKeyboard() const;
    //const std::unique_ptr<Gamepad>& GetGamepad() const;

/* @section Private variable */
public:
    InputManager m_inputManager;
    
    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    //std::unique_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
