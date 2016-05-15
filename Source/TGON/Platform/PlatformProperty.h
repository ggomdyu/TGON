/*
* Author : Junho-Cha
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Config/Property/Windows/WindowsProperty.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Config/Property/Android/AndroidProperty.h"
#endif