/**
 * @file    MouseType.h
 * @author  ggomdyu
 * @since   06/12/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouseType.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouseType.h"
#endif
