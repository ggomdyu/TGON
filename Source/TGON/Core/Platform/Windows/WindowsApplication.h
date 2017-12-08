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
    using BaseApplication::BaseApplication;

/* @section Public destructor */
public:
    virtual ~WindowsApplication() = default;

/* @section Public method */
public:
    virtual void MessageLoop() override;

    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIconType messageBoxType) const override;
    virtual void Terminate() override;

    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

/* @section Private method */
private:
    /* @brief   Register WNDCLASS which has Default window property given by engine. */
    bool RegisterWindowClass(HINSTANCE instanceHandle);
};

} /* namespace windows */

using Application = windows::WindowsApplication;

} /* namespace platform */
} /* namespace tgon */
