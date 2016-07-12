/*
* Author : Cha Junho
* Date : 04/02/2016
* Latest author :
* Latest date :
*/

#pragma once
#ifdef BOOST_OS_WINDOWS
	#include "../Config/Windows/WindowsProperty.h"
#elif BOOST_OS_ANDROID
	#include "../Math/Android/TMathNeon.h"
#endif