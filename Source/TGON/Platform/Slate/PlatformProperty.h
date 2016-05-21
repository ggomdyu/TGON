/*
* Author : Junho-Cha
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#if BOOST_OS_WINDOWS
	#include "../Property/Windows/WindowsProperty.h"
#elif BOOST_OS_ANDROID
	#include "../Property/Android/AndroidProperty.h"
#endif