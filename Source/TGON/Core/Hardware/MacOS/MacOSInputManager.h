/**
 * @file    MacOSInputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDeviceMouse;
class InputDeviceKeyboard;
class InputDevicePad;
class InputManager;

} /* namespace gainput */

namespace tgon
{
    
class Window;

class TGON_API MacOSInputManager :
    private boost::noncopyable
{
/**@section Public constructor */
public:
    explicit MacOSInputManager(const std::shared_ptr<Window>& window);
   
/**@section Public destructor */
public:
    ~MacOSInputManager();
    
/**@section Public method */
public:
    void Update();

    gainput::InputDeviceMouse* CreateNativeMouse();
    gainput::InputDeviceKeyboard* CreateNativeKeyboard();
    gainput::InputDevicePad* CreateNativeGamepad();

/**@section Private variable */
private:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};

} /* namespace tgon */
