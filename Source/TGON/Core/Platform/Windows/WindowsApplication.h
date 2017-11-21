/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include <Windows.h>

#include "Core/Platform/Config.h"
#include "Core/Platform/Base/BaseApplication.h"

namespace tgon
{
namespace platform
{
namespace windows
{

class TGON_API WindowsApplication :
    public BaseApplication
{
/* @section Public destructor */
public:
    WindowsApplication();
    virtual ~WindowsApplication() = default;

/* @section Public method */
public:
    void MessageLoop();

/* @section Private method */
private:
    /* @brief   Main Message procedure of application. */
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);
    
    /* @brief   Register WNDCLASS which has Default window property given by engine. */
    bool RegisterWindowClass(HINSTANCE instanceHandle);
};

} /* namespace windows */

using Application = windows::WindowsApplication;

} /* namespace platform */
} /* namespace tgon */
