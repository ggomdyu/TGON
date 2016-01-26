#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "..\..\TGON_Windows.Core\Sources\WindowsWindow.h"
#else
	#error	 "You're platform is not supported."
#endif