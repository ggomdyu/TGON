/**
 * filename TTime.h
 * author   ggomdyu
 * since    05/15/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Private/Windows/WindowsTime.h"
#elif BOOST_OS_ANDROID
#	include "Private/Android/AndroidTime.h"
#elif BOOST_OS_IOS
#	include "Private/iOS/iOSTime.h"
#endif