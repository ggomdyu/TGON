/**
 * @filename    WindowsInputManager.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <OIS.h>

#include "Core/Platform/Window.h"

namespace tgon
{

class TGON_API InputManagerImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    explicit InputManagerImpl(const Window& inputTarget);
    
/* @section Public destructor */
public:
    ~InputManagerImpl();

/* @section Public method */
public:
    /* @brief   Updates the input manager. */
    void Update();
    
    /* @brief   Creates a native mouse device. */
    OIS::Mouse* CreateMouseDevice();

    /* @brief   Creates a native keyboard device. */
    OIS::Keyboard* CreateKeyboardDevice();

    /* @brief   Creates a native gamepad device. */
    OIS::JoyStick* CreateGamepadDevice();

/* @section Private method */
private:
    OIS::ParamList QueryParamList(const Window& inputTarget) const;
    
/* @section Protected variable */
protected:
    OIS::InputManager* m_inputManager;
};

} /* namespace tgon */
