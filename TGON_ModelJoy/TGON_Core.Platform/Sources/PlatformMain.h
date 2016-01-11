#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "Windows\WindowsMain.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidMain.h"
#endif