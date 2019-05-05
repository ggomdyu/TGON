/**
 * @file    Application.h
 * @author  ggomdyu
 * @since   04/01/2016
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Object/DelegateChain.h"
#include "Core/Engine/Engine.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplication.h"
#endif

#include "Window.h"

namespace tgon
{

class TGON_API Application final :
    private PlatformApplication
{
public:
    TGON_DECLARE_RTTI(Application);

/**@section Constructor */
private:
    explicit Application();

/**@section Method */
public:
    static Application* GetInstance();

    void MessageLoop();
    void ShowMessageBox(const char* message) const;
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    void ShowMessageBox(const char* title, const char* message) const;
    std::shared_ptr<Engine> GetEngine() noexcept;
    std::shared_ptr<const Engine> GetEngine() const noexcept;
    std::shared_ptr<Window> GetRootWindow() noexcept;
    std::shared_ptr<const Window> GetRootWindow() const noexcept;
    PlatformApplication* GetPlatformDependency() noexcept;
    const PlatformApplication* GetPlatformDependency() const noexcept;
    
    using PlatformApplication::ShowMessageBox;
    using PlatformApplication::Terminate;
    
/**@section Event Handler */
public:
    void OnLaunch();
    void OnTerminate();
    
/**@section Variable */
protected:
    std::shared_ptr<Window> m_rootWindow;
    std::shared_ptr<Engine> m_engine;
};

} /* namespace tgon */
