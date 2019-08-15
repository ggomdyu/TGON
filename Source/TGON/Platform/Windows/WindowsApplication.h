/**
 * @file    WindowsApplication.h
 * @author  ggomdyu
 * @since   02/13/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

namespace tgon
{

class TGON_API WindowsApplication :
    private boost::noncopyable
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

}                               
