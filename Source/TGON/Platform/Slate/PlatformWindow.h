/*
* Author : Cha Junho
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#	include "../Window/Windows/WindowsWindow.h"
#else BOOST_OS_ANDROID
#	include "../Window/Android/AndroidWindow.h"
#endif