/**
 * @filename    MacOSInputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <gainput/gainput.h>

#include "Core/Platform/Window.h"
#include "Core/Hardware/Generic/GenericInputManager.h"

namespace tgon
{
    
class MacOSInputManager :
    public GenericInputManager
{
/* @section Public constructor */
public:
    explicit MacOSInputManager(const std::shared_ptr<GenericWindow>& window);
    
/* @section Public destructor */
public:
    virtual ~MacOSInputManager() override = default;
    
/* @section Public method */
public:
    virtual void* CreateKeyboard() override;
    virtual void* CreateMouse() override;
    virtual void* CreateGamepad() override;
    
    virtual void Update() override;
    
/* @section Private variable */
private:
    gainput::InputManager m_inputManager;
};
    
using InputManager = MacOSInputManager;
    
} /* namespace tgon */
