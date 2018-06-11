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
public:
    TGON_RUNTIME_OBJECT(MacOSInputManager);

/* @section Public constructor */
public:
    explicit MacOSInputManager(const Window& window);
    
/* @section Public destructor */
public:
    virtual ~MacOSInputManager() override = default;
    
/* @section Public method */
public:
    virtual void Update() override;
    
/* @section Protected variable */
protected:
    gainput::InputManager m_inputManager;
};

} /* namespace tgon */
