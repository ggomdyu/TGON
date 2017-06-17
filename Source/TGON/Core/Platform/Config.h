/**
 * @filename    Config.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsConfig.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidConfig.h"
#elif BOOST_OS_IOS
#	include "iOS/iOSConfig.h"
#endif
