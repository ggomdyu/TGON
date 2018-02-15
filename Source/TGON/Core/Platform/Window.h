/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       02/15/2018
 */

#pragma once
#include "Config.h"

#if BOOST_OS_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif BOOST_OS_MACOS
#   import "MacOS/MacOSWindow.h"
#elif BOOST_OS_ANDROID
#   include "Android/AndroidWindow.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSWindow.h"
#endif

#include <boost/preprocessor/cat.hpp>

namespace tgon
{
namespace core
{

class Window :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, Window)
{
public:
    TGON_RUNTIME_OBJECT(Window)

    /* @section Public constructor */
public:
    using SuperType::SuperType;
};

} /* namespace core */
} /* namespace tgon */
