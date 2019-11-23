/**
 * @file    Application.h
 * @author  ggomdyu
 * @since   04/01/2016
 */

#pragma once
#include <memory>

#include "Engine/Engine.h"

#include "Window.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   include "IOS/IOSApplication.h"
#endif

namespace tgon
{

enum class MessageBoxIcon
{
    No,
    Informational,
    Warning,
};

class Application final :
    private PlatformApplication
{
/**@section Constructor */
private:
    Application();

/**@section Method */
public:
    PlatformApplication& GetPlatformDependency() noexcept;
    const PlatformApplication& GetPlatformDependency() const noexcept;
    static Application& GetInstance();
    void MessageLoop();
    [[noreturn]] static void Terminate();
    static void ShowMessageBox(const char* message);
    static void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon);
    static void ShowMessageBox(const char* title, const char* message);
    static void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon);
    static std::shared_ptr<Engine> GetEngine() noexcept;
    static std::shared_ptr<Window> GetRootWindow() noexcept;
    
/**@section Event Handler */
public:
    static void OnLaunch();
    static void OnTerminate();
    
/**@section Variable */
protected:
    std::shared_ptr<Engine> m_engine;
    std::shared_ptr<Window> m_rootWindow;
};

} /* namespace tgon */
