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
public:
    TGON_RUNTIME_OBJECT(WindowsInputManager);

/* @section Public constructor */
public:
    explicit WindowsInputManager(const Window& window);
    
/* @section Public destructor */
public:
    virtual ~WindowsInputManager() override;

/* @section Public method */
public:
    virtual void Update() override;

/* @section Private method */
public:
    OIS::ParamList QueryParamList(const Window& window) const;
    
/* @section Protected variable */
protected:
    OIS::InputManager* m_inputManager;
};

} /* namespace tgon */
