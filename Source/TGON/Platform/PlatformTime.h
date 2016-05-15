/*
* Author : Junho-Cha
* Date : 05/15/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Time/Windows/WindowsTime.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Time/Android/WindowsTime.h"
#endif