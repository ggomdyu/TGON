/**
 * @file    WindowsInputManager.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>
#include <OIS.h>

#include "Core/Object/CoreObject.h"
#include "Core/Platform/Window.h"

namespace tgon
{

class TGON_API WindowsInputManager :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(WindowsInputManager);

/**@section Constructor */
public:
    explicit WindowsInputManager(const std::shared_ptr<Window>& inputTarget);
    
/**@section Destructor */
public:
    ~WindowsInputManager();

/**@section Method */
public:
    void Update();

protected:
    OIS::Mouse* CreateNativeMouse();
    OIS::Keyboard* CreateNativeKeyboard();
    OIS::JoyStick* CreateNativeGamepad();

private:
    OIS::ParamList QueryParamList(const std::shared_ptr<Window>& inputTarget) const;
    
/**@section Variable */
protected:
    OIS::InputManager* m_inputManager;
};

using PlatformInputManager = WindowsInputManager;

} /* namespace tgon */
