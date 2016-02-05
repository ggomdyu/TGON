#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "..\..\TGON_Windows.Core\Sources\WindowsConsole.h"
#else
#endif


namespace tgon
{
	typedef ConsoleImpl TConsole;
}