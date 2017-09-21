/**
 * @filename    BaseApplication.h
 * @author      ggomdyu
 * @since       08/24/2017
 * @brief       Set of Plaform-agnostic Application interface.
 */

#pragma once
#include <type_traits>

#include "Core/Platform/Config.h"

// static_assert(std::is_convertible<className*, BaseApplication*>::value)
#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace platform\
    {\
    std::shared_ptr<class BaseApplication> MakeApplication()\
    {\
        return std::make_shared<className>();\
    }\
    } /* namespace platform */\
    } /* namespace tgon */

namespace tgon
{
namespace platform
{

class TGON_API BaseApplication
{
public:
    virtual void OnLaunch() {}
    virtual void OnTerminate() {}
    virtual void OnUpdate() {}
    virtual void OnDraw() {}
};

} /* namespace platform */
} /* namespace tgon */
