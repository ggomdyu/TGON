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

/**@section Private constructor */
private:
    explicit Application();

/**@section Public method */
public:
    /**@brief   Gets the global instance of this class. */
    static Application* GetInstance();

    /**@brief   Loops the message queue and handles messages. */
    void MessageLoop();

    /**@brief   Terminates currently running application. */
    using PlatformApplication::Terminate;
    
    /**
     * @brief   Displays a message window which presents a message to user.
     * @param [in] message  The message appears in the message window.
     */
    void ShowMessageBox(const char* message) const;
    
    /**
     * @brief   Displays a message window which presents a message to user.
     * @param [in] message          The message appears in the message window.
     * @param [in] messageBoxIcon   The type of icon appears in the message window.
     */
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /**
     * @brief   Displays a message window which presents a message to user.
     * @param [in] title    The title appears in the message window.
     * @param [in] message  The message appears in the message window.
     */
    void ShowMessageBox(const char* title, const char* message) const;
    
    using PlatformApplication::ShowMessageBox;

    using PlatformApplication::EnableCrashHandler;

    /**@brief   Gets the Engine managed by application. */
    static Engine* GetEngine() noexcept;

    /**@brief   Gets the root window. */
    static Window& GetRootWindow() noexcept;
    
/**@section Public event handler */
public:
    void OnDidLaunch();

    void OnWillTerminate();
    
/**@section Protected variable */
protected:
    std::unique_ptr<Window> m_rootWindow;
    std::unique_ptr<Engine> m_engine;
};

} /* namespace tgon */
