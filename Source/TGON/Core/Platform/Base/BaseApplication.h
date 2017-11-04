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

#include "BaseApplicationFwd.h"

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
/* @section Public destructor */
public:
    virtual ~BaseApplication() = default;

/* @section Public method */
public:
    void InitWithWindow(const std::shared_ptr<BaseWindow>& window);

    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType) = 0;
    virtual void Terminate() = 0;

    const std::shared_ptr<BaseWindow>& GetMainWindow() const;

    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnDidTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<BaseWindow>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<BaseWindow>&) {}
    virtual void OnUpdate() {}
    virtual void OnDraw() {}

protected:
    std::shared_ptr<BaseWindow> m_mainWindow;
};

} /* namespace platform */
} /* namespace tgon */
