/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include "Config.h"
#include "ApplicationFwd.h"

#include <boost/predef/os.h>
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace platform\
    {\
    std::shared_ptr<Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace platform */\
    } /* namespace tgon */

namespace tgon
{
namespace platform
{

class TGON_API Application :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Application() = default;
    explicit Application(const WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~Application() = default;

/* @section Public method */
public:
    void Initialize(const WindowStyle& windowStyle);

    void MessageLoop();
    void Terminate();
    void ShowMessageBox(const char* message) const;
    void ShowMessageBox(const char* message, MessageBoxIconType iconType) const;
    void ShowMessageBox(const char* title, const char* message) const;
    void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const;

#if BOOST_OS_WINDOWS
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);
#elif BOOST_OS_MACOS
    void OnHandleMessage(NSEvent* message);
#endif
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<Window>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<Window>&) {}
    virtual void OnUpdate() {}

    const std::shared_ptr<Window>& GetMainWindow() const noexcept;

protected:
    std::shared_ptr<Window> m_mainWindow;
};

} /* namespace platform */
} /* namespace tgon */