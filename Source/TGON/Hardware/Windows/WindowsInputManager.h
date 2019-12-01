/**
 * @file    WindowsInputManager.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <OIS.h>

#include "Core/NonCopyable.h"

#pragma comment(lib, "dinput8.lib")

namespace tgon
{

class WindowsInputManager :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit WindowsInputManager(OIS::InputManager* inputManager) noexcept;

/**@section Method */
public:    
    OIS::Mouse* CreateNativeMouse();
    OIS::Keyboard* CreateNativeKeyboard();
    OIS::JoyStick* CreateNativeGamepad();
    OIS::ParamList QueryParamList(const Window& inputTargetWindow) const;
    OIS::InputManager* GetInputManager() noexcept;
    const OIS::InputManager* GetInputManager() const noexcept;

/**@section Variable */
protected:
    OIS::InputManager* m_inputManager;
};

using PlatformInputManager = WindowsInputManager;

} /* namespace tgon */
