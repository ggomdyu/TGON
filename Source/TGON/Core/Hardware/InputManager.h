/**
 * @filename    InputManager.h
 * @author      ggomdyu
 * @since       05/17/2017
 */

#pragma once
#include <boost/preprocessor/cat.hpp>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSInputManager..h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidInputManager..h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSInputManager..h"
#endif

namespace tgon
{

class InputManager :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, InputManager)
{
public:
    TGON_RUNTIME_OBJECT(InputManager)

/* @section Public constructor */
public:
    using SuperType::SuperType;
};

} /* namespace tgon */