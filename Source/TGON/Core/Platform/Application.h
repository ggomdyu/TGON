/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/preprocessor/cat.hpp>
#include <vector>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplication.h"
#endif

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    std::shared_ptr<Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace tgon */

namespace tgon
{

class Application :
    public BOOST_PP_CAT(TGON_PLATFORM_NAME, Application)
{
public:
    TGON_RUNTIME_OBJECT(Application)

/* @section Public constructor */
public:
    using SuperType::SuperType;

/* @section Public method */
public:
    static const std::shared_ptr<Application>& GetInstance();
};

} /* namespace tgon */