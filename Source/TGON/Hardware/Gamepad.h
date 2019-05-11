/**
 * @file    Gamepad.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif

namespace tgon
{

class TGON_API Gamepad final :
    private PlatformGamepad
{
/**@section Constructor */
public:
    using PlatformGamepad::PlatformGamepad;

/**@section Method */
public:
    using PlatformGamepad::Update;
    using PlatformGamepad::Vibrate;
    using PlatformGamepad::IsButtonDown;
    using PlatformGamepad::IsButtonHold;
    using PlatformGamepad::IsButtonUp;
};
    
} /* namespace tgon */
