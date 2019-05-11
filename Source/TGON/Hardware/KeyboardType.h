/**
 * @file    KeyboardType.h
 * @author  ggomdyu
 * @since   06/12/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboardType.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboardType.h"
#endif
