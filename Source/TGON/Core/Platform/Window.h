/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       02/15/2018
 */

#pragma once
#include <boost/preprocessor/cat.hpp>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSWindow.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidWindow.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSWindow.h"
#endif

namespace tgon
{

class Window :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, Window)
{
public:
    TGON_RUNTIME_OBJECT(Window)

/* @section Public constructor */
public:
    using SuperType::SuperType;

/* @section Public destructor */
public:
    virtual ~Window() final override = default;

/* @section Public operator */
public:
    Window& operator=(Window&&) = default;
    Window& operator=(const Window&) = default;
};

} /* namespace tgon */