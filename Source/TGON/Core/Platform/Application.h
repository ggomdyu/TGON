/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif BOOST_OS_MACOS
#   import "MacOS/MacOSApplication.h"
#elif BOOST_OS_ANDROID
#   include "Android/AndroidApplication.h"
#elif BOOST_OS_IOS
#   import "iOS/iOSApplication.h"
#endif
