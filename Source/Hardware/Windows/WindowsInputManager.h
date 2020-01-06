/**
 * @file    WindowsInputManager.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <OIS.h>

#include "Core/NonCopyable.h"

namespace tgon
{

class WindowsInputManager :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit WindowsInputManager(const class Window& inputTarget);
    WindowsInputManager(WindowsInputManager&& rhs) noexcept;

/**@section Destructor */
public:
    ~WindowsInputManager();

/**@section Method */
public:
    OIS::Mouse* CreateNativeMouse();
    OIS::Keyboard* CreateNativeKeyboard();
    OIS::JoyStick* CreateNativeGamepad();
    OIS::InputManager* GetInputManager() noexcept;
    const OIS::InputManager* GetInputManager() const noexcept;

/**@section Variable */
protected:
    OIS::InputManager* m_inputManager = nullptr;
};

using PlatformInputManager = WindowsInputManager;

} /* namespace tgon */
