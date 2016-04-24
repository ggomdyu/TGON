/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include "../Config/Platform/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../../Math/Windows/WindowsPlatformMath.h"
#elif TGON_PLATFORM_ANDROID
	#include "../../Math/Windows/AndroidPlatformMath.h"
#elif TGON_PLATFORM_LINUX
	#include "../../Math/Windows/LinuxPlatformMath.h"
#endif