/**
 * @file    MacOSInputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Platform/Config.h"

namespace gainput
{
    
class InputDeviceMouse;
class InputDeviceKeyboard;
class InputDevicePad;
class InputManager;

} /* namespace gainput */

namespace tgon
{
    
class MacOSWindow;

class TGON_API MacOSInputManager :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit MacOSInputManager(const MacOSWindow& window);
   
/**@section Destructor */
public:
    ~MacOSInputManager();
    
/**@section Method */
public:
    void Update();

    gainput::InputDeviceMouse* CreateNativeMouse();
    gainput::InputDeviceKeyboard* CreateNativeKeyboard();
    gainput::InputDevicePad* CreateNativeGamepad();

/**@section Variable */
private:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};
    
using PlatformInputManager = MacOSInputManager;

} /* namespace tgon */
