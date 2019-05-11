/**
 * @file    WindowsInputManager.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <memory>
#include <OIS.h>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"

namespace OIS
{

} /* namespace OIS */

namespace tgon
{

class WindowsWindow;

class TGON_API WindowsInputManager :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsInputManager(const WindowsWindow& inputTarget);
    
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
    OIS::ParamList QueryParamList(const WindowsWindow& inputTarget) const;
    
/**@section Variable */
protected:
    OIS::InputManager* m_inputManager;
};

using PlatformInputManager = WindowsInputManager;

} /* namespace tgon */
