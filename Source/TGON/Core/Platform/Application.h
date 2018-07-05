/**
 * @file    Application.h
 * @author  ggomdyu
 * @since   04/01/2016
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Delegate.h"
#include "Core/Object/Engine.h"

namespace tgon
{

class ApplicationImpl;
class Window;
enum class MessageBoxIcon;

class TGON_API Application :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    explicit Application(std::unique_ptr<Engine> engine);
    
/* @section Public destructor */
public:
    virtual ~Application();

/* @section Public method */
public:
    /* @brief   Returns the global instance of this class. */
    static Application& GetInstance() noexcept;

    /* @brief   Loops the message queue and handle the message. */
    void MessageLoop();
    
    /* @brief   Terminates the program forcibly. */
    void Terminate();
    
    /**
     * @brief               Shows a message box in front of screen.
     * @param [in] message  The message what you want to show in description area.
     */
    void ShowMessageBox(const char* message) const;
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] message          The message what you want to show in description area.
     * @param [in] messageBoxIcon   The type of icon in message box.
     */
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /**
     * @brief               Shows a message box in front of screen.
     * @param [in] title    The message what you want to show in title area.
     * @param [in] message  The message what you want to show in description area.
     */
    void ShowMessageBox(const char* title, const char* message) const;
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] title            The message what you want to show in title area.
     * @param [in] message          The message what you want to show in description area.
     * @param [in] messageBoxIcon   The type of icon in message box.
     */
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /* @brief   Gets the root window. */
    Window& GetRootWindow() noexcept;
    
    /* @brief   Gets the root window. */
    const Window& GetRootWindow() const noexcept;
    
    /* @brief   Gets the engine. */
    const Engine& GetEngine() const noexcept;

    /* @brief   Gets the engine. */
    Engine& GetEngine() noexcept;

    const ApplicationImpl& GetImpl() const noexcept;

    ApplicationImpl& GetImpl() noexcept;

/* @section Private method */
private:
    /* @brief   Updates the application. */
    void Update();

/* @section Public event handler */
public:
    void OnDidLaunch();
    void OnWillTerminate();
    
/* @section Protected variable */
protected:
    std::unique_ptr<ApplicationImpl> m_applicationImpl;

    std::unique_ptr<Engine> m_engine;
    std::unique_ptr<Window> m_rootWindow;
};

} /* namespace tgon */
