#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsWindow.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidWindow.h"
#endif