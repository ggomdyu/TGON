/**
 * @file    WindowsApplication.h
 * @author  ggomdyu
 * @since   02/13/2018
 */

#pragma once
#include "Core/NonCopyable.h"

namespace tgon
{

class WindowsApplication :
    private NonCopyable
{
/**@section Constructor */
protected:
    WindowsApplication();

/**@section Method */
private:
    /**@brief   Register default WNDCLASS to window class table. */
    static bool RegisterDefaultWindowClass();
};

using PlatformApplication = WindowsApplication;

} /* namespace tgon */                               
