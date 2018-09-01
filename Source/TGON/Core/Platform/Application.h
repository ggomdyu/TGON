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
    TGON_RUNTIME_OBJECT(Application);

/* @section Private constructor */
private:
    explicit Application();

/* @section Public method */
public:
    /* @brief   Loops the message queue and handle the message. */
    static Application* GetInstance();

    void MessageLoop();

    using PlatformApplication::Terminate;
    
    /**
     * @brief   Displays a message box.
     * @param [in] message  The message to show in description area.
     */
    void ShowMessageBox(const char* message) const;
    
    /**
     * @brief   Displays a message box.
     * @param [in] message          The message to show in description area.
     * @param [in] messageBoxIcon   The type of icon appears in the message box.
     */
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /**
     * @brief   Displays a message box.
     * @param [in] title    The message to show in title area.
     * @param [in] message  The message to show in description area.
     */
    void ShowMessageBox(const char* title, const char* message) const;
    
    using PlatformApplication::ShowMessageBox;

    /* @brief   Gets the Engine. */
    Engine* GetEngine();

    /* @brief   Gets the Engine. */
    const Engine* GetEngine() const;

    /* @brief   Gets the root window. */
    Window& GetRootWindow() noexcept;
    
    /* @brief   Gets the root window. */
    const Window& GetRootWindow() const noexcept;

/* @section Public event handler */
public:
    void OnDidLaunch();

    void OnWillTerminate();
    
/* @section Protected variable */
protected:
    std::unique_ptr<Window> m_rootWindow;
    std::unique_ptr<Engine> m_engine;
};

} /* namespace tgon */
