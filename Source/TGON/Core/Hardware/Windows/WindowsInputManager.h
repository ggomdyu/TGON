/**
 * @filename    WindowsInputManager.h
 * @author      ggomdyu
 * @since       05/18/2018
 */

#pragma once
#include <OIS.h>

#include "Core/Platform/Window.h"

#include "../Generic/GenericInputManager.h"

namespace tgon
{

class WindowsInputManager :
    public GenericInputManager
{
public:
    TGON_RUNTIME_OBJECT(WindowsInputManager);

/* @section Public constructor */
public:
    WindowsInputManager();
    WindowsInputManager(const Window& window);

/* @section Public destructor */
public:
    virtual ~WindowsInputManager();

/* @section Public method */
public:
    void Initialize(const Window& window);

private:
    OIS::ParamList QueryParamList(const Window& window);
    
/* @section Private variable */
private:
    OIS::InputManager* m_nativeInputManager;
};

} /* namespace tgon */