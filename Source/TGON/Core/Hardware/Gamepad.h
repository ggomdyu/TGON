/**
 * @filename    Gamepad.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif
