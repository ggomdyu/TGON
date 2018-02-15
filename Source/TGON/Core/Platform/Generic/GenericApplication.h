/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include "GenericApplicationFwd.h"

#include "../Config.h"

#include "Core/Object/Object.h"

#include <boost/predef/os.h>
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace core\
    {\
    std::shared_ptr<GenericApplication> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, GenericApplication*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from GenericApplication.");\
        return std::make_shared<className>();\
    }\
    } /* namespace core */\
    } /* namespace tgon */

namespace tgon
{
namespace core
{

class TGON_API GenericApplication :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GenericApplication)

/* @section Public constructor */
public:
    GenericApplication() = default;
    GenericApplication(const std::shared_ptr<GenericWindow>& window);

/* @section Public destructor */
public:
    virtual ~GenericApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() = 0;
    virtual void Terminate() = 0;
    virtual void ShowMessageBox(const char* message) const;
    virtual void ShowMessageBox(const char* message, MessageBoxIconType iconType) const;
    virtual void ShowMessageBox(const char* title, const char* message) const;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const = 0;

    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnUpdate() {}

    const std::shared_ptr<GenericWindow>& GetRootWindow() const noexcept;

protected:
    std::shared_ptr<GenericWindow> m_rootWindow;
};

} /* namespace core */
} /* namespace tgon */
