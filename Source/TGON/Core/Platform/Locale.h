/**
 * @filename    TLocale.h
 * @author      ggomdyu
 * @since       06/14/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsLocale.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidLocale.h"
#elif BOOST_OS_IOS
#	import "iOS/iOSLocale.h"
#endif
