/*
* Author : Junho-Cha
* Date : 2016-04-02
* Latest author :
* Latest date :
*/

#pragma once
#include "Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../../Math/Windows/TMathSSE2.h"
#elif TGON_PLATFORM_ANDROID
	#include "../../Math/Android/TMathNeon.h"
#elif TGON_PLATFORM_LINUX
#endif