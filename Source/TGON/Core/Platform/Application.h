/**
 * @file    Application.h
 * @author  ggomdyu
 * @since   04/01/2016
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Object/DelegateChain.h"

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
    private boost::noncopyable
{
/* @section Private constructor */
private:
    explicit Application();
    
/* @section Public method */
public:
    /* @brief                       Gets the global instance of this class. */
    static Application* GetInstance();

    /* @brief                       Loops the message queue and handle the message. */
    template <typename _FunctionType>
    void MessageLoop(const _FunctionType& onUpdate);

    /* @brief                       Terminates the program forcibly. */
    void Terminate();
    
    /**
     * @brief                       Displays a message box.
     * @param [in] message          The message to show in description area.
     */
    void ShowMessageBox(const char* message) const;
    
    /**
     * @brief                       Displays a message box.
     * @param [in] message          The message to show in description area.
     * @param [in] messageBoxIcon   The type of icon appears in the message box.
     */
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /**
     * @brief                       Displays a message box.
     * @param [in] title            The message to show in title area.
     * @param [in] message          The message to show in description area.
     */
    void ShowMessageBox(const char* title, const char* message) const;
    
    /**
     * @brief                       Displays a message box.
     * @param [in] title            The message to show in title area.
     * @param [in] message          The message to show in description area.
     * @param [in] messageBoxIcon   The type of icon appears in the message box.
     */
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /* @brief   Gets the root window. */
    Window& GetRootWindow() noexcept;
    
    /* @brief   Gets the root window. */
    const Window& GetRootWindow() const noexcept;

/* @section Public event handler */
public:
    DelegateChain<void()> OnDidLaunch;
    DelegateChain<void()> OnWillTerminate;
    
/* @section Protected variable */
protected:
    ApplicationImpl m_applicationImpl;
    
    std::unique_ptr<Window> m_rootWindow;
};

template <typename _FunctionType>
void Application::MessageLoop(const _FunctionType& onUpdate)
{
    m_applicationImpl.MessageLoop(onUpdate);
}

} /* namespace tgon */
