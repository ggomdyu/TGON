/*
* Author : Junho-Cha
* Date : 04/01/2016
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