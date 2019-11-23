/**
 * @file    MacOSInputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <gainput/gainput.h>

#include "Core/NonCopyable.h"

namespace tgon
{

class MacOSInputManager :
    private NonCopyable
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
