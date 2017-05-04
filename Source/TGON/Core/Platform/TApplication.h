/**
 * @filename    TApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsApplication.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidApplication.h"
#endif