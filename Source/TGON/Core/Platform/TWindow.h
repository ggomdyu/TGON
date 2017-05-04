/**
 * @filename PlatformWindow.h
 * @author   ggomdyu
 * since    04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsWindow.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidWindow.h"
#endif

namespace tgon
{

template <typename WindowTy, 
		  typename = typename std::enable_if<std::is_convertible<WindowTy*, window::TWindow*>::value>::type>
std::shared_ptr<WindowTy> MakeWindow(const window::WindowStyle& wndStyle = window::WindowStyle{})
{
	return std::make_shared<WindowTy>(wndStyle);
}

}