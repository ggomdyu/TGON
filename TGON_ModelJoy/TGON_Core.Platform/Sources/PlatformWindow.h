#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "Windows\WindowsWindow.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidWindow.h"
#endif