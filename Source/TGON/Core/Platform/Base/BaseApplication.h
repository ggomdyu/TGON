/**
 * @filename    BaseApplication.h
 * @author      ggomdyu
 * @since       08/24/2017
 * @brief       Set of Plaform-agnostic Application interface.
 */

#pragma once
#include <type_traits>
#include <memory>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

#include "BaseApplicationType.h"

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace platform\
    {\
    std::shared_ptr<class BaseApplication> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, BaseApplication*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from BaseApplication.");\
        return std::make_shared<className>();\
    }\
    } /* namespace platform */\
    } /* namespace tgon */

namespace tgon
{
namespace platform
{

class TGON_API BaseApplication :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    BaseApplication(const std::shared_ptr<class BaseWindow>& mainWindow);

/* @section Public destructor */
public:
    virtual ~BaseApplication() = default;

/* @section Public method */
public:
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType) = 0;

    const std::shared_ptr<class BaseWindow>& GetMainWindow() const;

    virtual void OnTerminate() {}
    virtual void OnUpdate() {}
    virtual void OnDraw() {}

private:
    std::shared_ptr<class BaseWindow> m_mainWindow;
};

} /* namespace platform */
} /* namespace tgon */
