/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif BOOST_OS_MACOS
#   import "MacOS/MacOSWindow.h"
#elif BOOST_OS_ANDROID
#   include "Android/AndroidWindow.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSWindow.h"
#endif
