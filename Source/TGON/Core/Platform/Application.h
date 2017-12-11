/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       Set of Plaform-agnostic Application interface.
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>

#include "Core/Platform/Config.h"

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace platform\
    {\
    std::shared_ptr<class Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, class Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace platform */\
    } /* namespace tgon */

namespace tgon
{
namespace platform
{

enum class MessageBoxIconType;

class TGON_API Application :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Application() = default;
    explicit Application(const struct WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~Application() = default;

/* @section Public method */
public:
    void Initialize(const struct WindowStyle& windowStyle);

    void MessageLoop();
    void Terminate();
    void ShowMessageBox(const char* message) const;
    void ShowMessageBox(const char* message, MessageBoxIconType iconType) const;
    void ShowMessageBox(const char* title, const char* message) const;
    void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const;

    void OnHandleMessage(const struct AppMessage& appMsg);
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<class Window>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<class Window>&) {}
    virtual void OnUpdate() {}

    const struct BatteryState GetBatteryState() const;
    const std::shared_ptr<class Window>& GetMainWindow() const noexcept;

protected:
    std::shared_ptr<class Window> m_mainWindow;
};

} /* namespace platform */
} /* namespace tgon */
