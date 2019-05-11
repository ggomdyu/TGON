/**
 * @file    Keyboard.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif

namespace tgon
{

class TGON_API Keyboard final :
    private PlatformKeyboard
{
/**@section Constructor */
public:
    using PlatformKeyboard::PlatformKeyboard;
    
/**@section Method */
public:
    using PlatformKeyboard::Update;
    using PlatformKeyboard::IsKeyDown;
    using PlatformKeyboard::IsKeyHold;
    using PlatformKeyboard::IsKeyUp;  
};
    
} /* namespace tgon */
