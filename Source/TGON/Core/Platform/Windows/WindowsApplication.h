/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include <Windows.h>

#include "Core/Platform/Base/BaseApplication.h"

namespace tgon
{
namespace platform
{

class BaseWindow;

namespace windows
{

class TGON_API WindowsApplication :
    public BaseApplication
{
/* @section Public constructor */
public:
    explicit WindowsApplication(const std::shared_ptr<BaseWindow>& mainWindow);

/* @section Public destructor */
public:
    virtual ~WindowsApplication() = default;

/* @section Public method */
public:
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType) override;

    void MessageLoop();

    /* @brief   Main Message procedure of application. */
<<<<<<< HEAD
    static LRESULT CALLBACK OnMessageHandled(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

/* @section Private method */
private:
=======
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);
    
    /* @brief   Register WNDCLASS which has Default window property given by engine. */
    bool RegisterWindowClass(HINSTANCE instanceHandle);
>>>>>>> 9e432bd77dd28cb655802278389d8517d3e18c16
};

} /* namespace windows */

using Application = windows::WindowsApplication;

} /* namespace platform */
} /* namespace tgon */
