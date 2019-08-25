/**
 * @file    MacOSInputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <gainput/gainput.h>

namespace tgon
{

class TGON_API MacOSInputManager :
    private boost::noncopyable
{
/**@section Method */
public:
    gainput::InputDeviceMouse* CreateNativeMouse();
    gainput::InputDeviceKeyboard* CreateNativeKeyboard();
    gainput::InputDevicePad* CreateNativeGamepad();

/**@section Variable */
protected:
    gainput::InputManager m_inputManager;
};
    
using PlatformInputManager = MacOSInputManager;

} /* namespace tgon */
