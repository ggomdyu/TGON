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
#include "Core/Object/IModule.h"
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
    template <typename _ModuleType, typename... _Args>
    void AddModule(_Args&&... args);
    void AddModule(const std::shared_ptr<IModule>& module);
    void AddModule(std::initializer_list<const std::shared_ptr<IModule>&> modules);
    template <typename _ModuleType>
    void GetModule();

/* @section Public event handler */
public:
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnUpdate();

/* @section Protected variable */
protected:
    std::shared_ptr<GenericWindow> m_rootWindow;
    std::vector<std::shared_ptr<IModule>> m_modules;
};

template<typename _ModuleType, typename ..._Args>
inline void GenericApplication::AddModule(_Args&&... args)
{
    m_modules.push_back(std::make_shared<_ModuleType>(std::forward<_Args>(args)...));
}

} /* namespace tgon */
