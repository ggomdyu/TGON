/**
 * @filename    Keyboard.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif

namespace tgon
{

class Keyboard :
    private BOOST_PP_CAT(TGON_PLATFORM_NAME, Keyboard)
{
public:
    TGON_RUNTIME_OBJECT(Keyboard);
    
/* @section Public constructor */
public:
    using SuperType::SuperType;
    
/* @section Public method */
public:
    using SuperType::Update;
    using SuperType::IsKeyDown;
    using SuperType::IsKeyHold;
    using SuperType::IsKeyUp;
};

} /* namespace tgon */
