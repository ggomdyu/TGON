/*
* Author : Junho-Cha
* Date : 2016-04-01
* Latest author :
* Latest date :
*/

#pragma once
#include "Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Property/Windows/WindowsProperty.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Property/Android/AndroidProperty.h"
#endif