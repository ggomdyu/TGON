/**
 * @file    Mouse.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Point.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif

namespace tgon
{
    
class TGON_API Mouse final :
    private PlatformMouse
{
/**@section Constructor */
public:
    using PlatformMouse::PlatformMouse;
    
/**@section Method */
public:
    static I32Point GetPosition();
    using PlatformMouse::GetPosition;
    using PlatformMouse::Update;
    using PlatformMouse::IsMouseDown;
    using PlatformMouse::IsMouseHold;
    using PlatformMouse::IsMouseUp;
};
    
} /* namespace tgon */
