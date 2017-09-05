/**
 * @filename    Camera.h
 * @author      ggomdyu
 * @since       09/01/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsCamera.h"
#elif BOOST_OS_MACOS
#	import "MacOS/MacOSCamera.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidCamera.h"
#elif BOOST_OS_IOS
#	import "IOS/IOSCamera.h"
#endif
