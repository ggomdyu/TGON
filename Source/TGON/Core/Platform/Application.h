/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include "Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplication.h"
#endif

#include <boost/preprocessor/cat.hpp>

namespace tgon
{
namespace core
{

class Application :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, Application)
{
public:
    TGON_RUNTIME_OBJECT(Application)

/* @section Public constructor */
public:
    Application();
    Application(const WindowStyle& windowStyle);

/* @section Public method */
public:
    static Application* GetInstance();
};

} /* namespace core */
} /* namespace tgon */
