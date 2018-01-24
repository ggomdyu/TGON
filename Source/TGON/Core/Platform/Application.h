/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include "ApplicationFwd.h"
#include "Config.h"

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
    std::shared_ptr<Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace core */\
    } /* namespace tgon */

namespace tgon
{
namespace core
{

class TGON_API Application :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(Application)

/* @section Public constructor */
public:
    Application() = default;
    explicit Application(const WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~Application() override = default;

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

} /* namespace core */
} /* namespace tgon */