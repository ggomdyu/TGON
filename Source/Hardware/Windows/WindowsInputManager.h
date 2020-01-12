/**
 * @file    WindowsInputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <gainput/gainput.h>
#include <memory>

#include "Core/NonCopyable.h"

namespace tgon
{

class WindowsInputManager :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit WindowsInputManager(const class Window& inputTargetWindow);
    WindowsInputManager(WindowsInputManager&& rhs) noexcept;

/**@section Method */
public:
    gainput::InputDeviceMouse* CreateNativeMouse();
    gainput::InputDeviceKeyboard* CreateNativeKeyboard();

/**@section Variable */
protected:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};
    
using PlatformInputManager = WindowsInputManager;

} /* namespace tgon */
