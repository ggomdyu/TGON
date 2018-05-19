/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The plaform-agnostic application interface.
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>

#include "Core/Object/Object.h"
#include "../Config.h"

#include "GenericApplicationFwd.h"

namespace tgon
{

class TGON_API GenericApplication :
    private boost::noncopyable,
    public Object
{
public:
    TGON_RUNTIME_OBJECT(GenericApplication)

/* @section Public constructor */
public:
    GenericApplication();
    GenericApplication(const std::shared_ptr<GenericWindow>& window);

/* @section Public destructor */
public:
    virtual ~GenericApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() = 0;
    virtual void Terminate() = 0;
    virtual void ShowMessageBox(const char* message) const;
    virtual void ShowMessageBox(const char* message, MessageBoxIcon iconType) const;
    virtual void ShowMessageBox(const char* title, const char* message) const;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIcon iconType) const = 0;

    const std::shared_ptr<GenericWindow>& GetRootWindow() const noexcept;

/* @section Public event handler */
public:
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnUpdate() {}

/* @section Protected variable */
protected:
    std::shared_ptr<GenericWindow> m_rootWindow;
};

} /* namespace tgon */
