/**
 * @file    InputModule.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>

#include "Hardware/InputManager.h"

#include "IModule.h"

namespace tgon
{
    
class Keyboard;
class Mouse;
class Gamepad;

struct InputMode final
{
    bool isUseKeyboard = true;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

class TGON_API InputModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(InputModule);
    
/**@section Constructor */
public:
    InputModule(const std::shared_ptr<Window>& inputTarget, const InputMode& inputMode = {});

/**@section Destructor */
public:
    virtual ~InputModule() final override;

/**@section Method */
public:
    virtual void Update() final override;
    
    const std::unique_ptr<Mouse>& GetMouse() const noexcept;
    const std::unique_ptr<Keyboard>& GetKeyboard() const noexcept;
    const std::unique_ptr<Gamepad>& GetGamepad() const noexcept;

/**@section Variable */
public:
    InputManager m_inputManager;

    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    std::unique_ptr<Gamepad> m_gamepad;
};

} /* namespace tgon */
