/*
* Author : Cha Junho
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#	include "../Config/Windows/WindowsProperty.h"
#elif BOOST_OS_ANDROID
#	include "../Config/Android/AndroidProperty.h"
#endif