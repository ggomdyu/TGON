/**
 * @file    ApplicationType.h
 * @author  ggomdyu
 * @since   06/28/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplicationType.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplicationType.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplicationType.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplicationType.h"
#endif