/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Math/Windows/TMathSSE2.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Math/Android/TMathNeon.h"
#elif TGON_PLATFORM_LINUX
#endif