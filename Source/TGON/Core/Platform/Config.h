/**
 * @file    Config.h
 * @author  ggomdyu
 * @since   04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   include "Windows/WindowsConfig.h"
#elif BOOST_OS_MACOS
#   import "MacOS/MacOSConfig.h"
#elif BOOST_OS_ANDROID
#   include "Android/AndroidConfig.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSConfig.h"
#endif
