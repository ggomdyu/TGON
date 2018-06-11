/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/Object/Object.h"
#include "Core/Object/Delegate.h"

#include "ApplicationFwd.h"

namespace tgon
{

class TGON_API Application :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(Application);
    
/* @section Public constructor */
public:
    Application();
    explicit Application(const WindowStyle& windowStyle);
    
/* @section Public destructor */
public:
    virtual ~Application();

/* @section Public method */
public:
    /* @brief                       Returns the global instance of this class. */
    static const std::shared_ptr<Application>& GetInstance();

    /* @brief                       Loops the message queue and handle it, or update the application. */
    void MessageLoop();
    
    /* @brief                       Terminates the program forcibly. */
    void Terminate();
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] message          The message what you want to show in description area.
     */
    void ShowMessageBox(const char* message) const;
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] message          The message what you want to show in description area.
     * @param [in] messageBoxIcon   The type of icon in message box.
     */
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] title            The message what you want to show in title area.
     * @param [in] message          The message what you want to show in description area.
     */
    void ShowMessageBox(const char* title, const char* message) const;
    
    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] title            The message what you want to show in title area.
     * @param [in] message          The message what you want to show in description area.
     * @param [in] messageBoxIcon   The type of icon in message box.
     */
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;
    
    /* @brief                       Sets the root window. */
    void SetRootWindow(const std::shared_ptr<Window>& window) noexcept;
    
    /* @brief                       Gets the root window. */
    std::weak_ptr<Window> GetRootWindow() noexcept;
    
    /* @brief                       Gets the root window. */
    std::weak_ptr<const Window> GetRootWindow() const noexcept;
    
    /* @brief                       Sets the engine. */
    void SetEngine(const std::shared_ptr<Engine>& engine) noexcept;
    
    /* @brief                       Gets the engine. */
    std::weak_ptr<Engine> GetEngine() noexcept;

    /* @brief                       Gets the engine. */
    std::weak_ptr<const Engine> GetEngine() const noexcept;

/* @section Public event handler */
public:
    virtual void OnDidLaunch();
    virtual void OnWillTerminate();
    
    Delegate<void(Window&)> OnWillCloseWindow;
    Delegate<void(Window&)> OnDidCloseWindow;
 
/* @section Private method */
private:
    /* @brief                       Updates the application. */
    void Update();
    
/* @section Protected variable */
protected:
    std::shared_ptr<ApplicationImpl> m_impl;
    std::shared_ptr<Engine> m_engine;
    
    std::shared_ptr<Window> m_rootWindow;
};

} /* namespace tgon */
