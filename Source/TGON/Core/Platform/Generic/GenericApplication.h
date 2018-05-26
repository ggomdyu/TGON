/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The plaform-agnostic application interface.
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <map>
#include <vector>

#include "Core/Object/Object.h"
#include "Core/Object/Module/IModule.h"

#include "GenericWindow.h"
#include "GenericApplicationType.h"

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
    GenericApplication(const std::shared_ptr<GenericWindow>& rootWindow);

/* @section Public destructor */
public:
    virtual ~GenericApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() = 0;
    virtual void Terminate() = 0;
    virtual void ShowMessageBox(const char* message) const;
    virtual void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    virtual void ShowMessageBox(const char* title, const char* message) const;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const = 0;
    const std::shared_ptr<GenericWindow>& GetRootWindow() const noexcept;
    template <typename _ModuleType, typename... _Args>
    void AddModule(_Args&&... args);
    void AddModule(const std::shared_ptr<IModule>& module);
    template <typename _ModuleType>
    IModule* GetModule();

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

    std::map<size_t, std::shared_ptr<IModule>> m_modulesToFind;
    std::vector<std::shared_ptr<IModule>> m_modules;
};

template<typename _ModuleType, typename ..._Args>
inline void GenericApplication::AddModule(_Args&& ...args)
{
    auto module = std::make_shared<_ModuleType>(std::forward<_Args>(args)...);

    m_modulesToFind.insert({ module->GetRTTI()->GetHashCode(), module });
    m_modules.push_back(module);
}

template<typename _ModuleType>
inline IModule* GenericApplication::GetModule()
{
    auto iter = m_modulesToFind.find(tgon::GetRTTI<_ModuleType>()->GetHashCode());
    if (iter == m_modulesToFind.end())
    {
        return nullptr;
    }

    return std::static_pointer_cast<_ModuleType>(iter->second);
}

} /* namespace tgon */
