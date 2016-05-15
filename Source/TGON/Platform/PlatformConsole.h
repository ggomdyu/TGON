#pragma once
#include "../Config/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Console/Windows/WindowsConsole.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Console/Windows/AndroidConsole.h"
#elif TGON_PLATFORM_LINUX
	#include "../Console/Windows/LinuxConsole.h"
#endif