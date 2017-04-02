/**
 * filename PlatformWindow.h
 * author   ggomdyu
 * since    04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Private/Windows/WindowsWindowFrame.h"
#endif

namespace tgon
{

template <typename WindowTy, 
		  typename = typename std::enable_if<std::is_convertible<WindowTy*, TWindowFrame*>::value>::type>
std::shared_ptr<WindowTy> MakeWindow(const WindowStyle& wndStyle = WindowStyle{})
{
	return std::make_shared<WindowTy>(wndStyle);
}

}