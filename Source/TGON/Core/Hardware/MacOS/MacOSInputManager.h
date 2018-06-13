/**
 * @filename    MacOSInputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#include "MacOSInputManagerFwd.h"

namespace tgon
{

class TGON_API InputManagerImpl final
{
/* @section Public constructor */
public:
    explicit InputManagerImpl(const Window& window);
   
/* @section Public destructor */
public:
    ~InputManagerImpl();
    
/* @section Public method */
public:
    void Update();
    
    gainput::InputDeviceMouse* CreateMouseDevice();
    gainput::InputDeviceKeyboard* CreateKeyboardDevice();
    gainput::InputDevicePad* CreateGamepadDevice();

/* @section Private variable */
private:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};

} /* namespace tgon */
