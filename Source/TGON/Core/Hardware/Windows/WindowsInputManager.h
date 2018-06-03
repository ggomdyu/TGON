/**
 * @filename    WindowsInputManager.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <OIS.h>

#include "Core/Platform/Window.h"
#include "Core/Hardware/Generic/GenericInputManager.h"

namespace tgon
{

class WindowsInputManager :
    public GenericInputManager
{
/* @section Public constructor */
public:
    explicit WindowsInputManager(const std::shared_ptr<GenericWindow>& window);
    
/* @section Public destructor */
public:
    virtual ~WindowsInputManager() override = default;

/* @section Public method */
public:
    virtual void* CreateKeyboard() const override;
    virtual void* CreateMouse() const override;
    virtual void* CreateGamepad() const override;

    virtual void Update() override;

/* @section Private method */
public:
    OIS::ParamList QueryParamList(const std::shared_ptr<GenericWindow>& window) const;
    
/* @section Private variable */
private:
    OIS::InputManager* m_inputManager;
};

using InputManager = WindowsInputManager;

} /* namespace tgon */
