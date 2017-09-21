/**
 * @filename    Screen.h
 * @author      ggomdyu
 * @since       07/05/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsScreen.h"
#if BOOST_OS_MACOS
#   import "MacOS/MacOSScreen.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidScreen.h"
#elif BOOST_OS_IOS
#	import "IOS/IOSScreen.h"
#endif
