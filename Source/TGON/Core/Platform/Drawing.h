/**
 * @filename    Drawing.h
 * @author      ggomdyu
 * @since       11/26/2017
 * @brief       Low level Platform-Specific drawing interface.
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   include "Windows/WindowsDrawing.h"
#elif BOOST_OS_MACOS
#   import "MacOS/MacOSDrawing.h"
#elif BOOST_OS_ANDROID
#   include "Android/AndroidDrawing.h"
#elif BOOST_OS_IOS
#   import "iOS/iOSDrawing.h"
#endif
