/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/preprocessor/cat.hpp>
#include <map>
#include <vector>
#include <memory>

#include "Core/Platform/Config.h"
#include "Core/Object/Module/IModule.h"

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

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    std::shared_ptr<Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace tgon */

namespace tgon
{

class Application
{
/* @section Public constructor */
public:
    explicit Application(const WindowStyle& windowStyle);
    
/* @section Public destructor */
public:
    virtual ~Application() = default;

/* @section Public method */
public:
    static const std::shared_ptr<Application>& GetInstance();

    void MessageLoop();
    void Terminate();
    void ShowMessageBox(const char* message) const;
    void ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const;
    void ShowMessageBox(const char* title, const char* message) const;
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;

    Window& GetRootWindow() noexcept;
    const Window& GetRootWindow() const noexcept;
    template <typename _ModuleType, typename... _Args>
    std::shared_ptr<_ModuleType> AddModule(_Args&&... args);
    void AddModule(const std::shared_ptr<IModule>& module);
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> GetModule() const;

/* @section Public event handler */
public:
    virtual void OnLaunch() {}
    virtual void OnTerminate() {}
    virtual void OnCloseWindow(const Window&) {}
    virtual void OnUpdate();

/* @section Protected variable */
protected:
    ApplicationImpl m_impl;

    Window m_rootWindow;

    std::map<size_t, std::shared_ptr<IModule>> m_modulesToFind;
    std::vector<std::shared_ptr<IModule>> m_modules;
};

template<typename _ModuleType, typename ..._Args>
inline std::shared_ptr<_ModuleType> Application::AddModule(_Args&& ...args)
{
    auto module = std::make_shared<_ModuleType>(std::forward<_Args>(args)...);

    auto pair = m_modulesToFind.insert({ module->GetRTTI()->GetHashCode(), module });
    if (pair.second == true)
    {
        m_modules.push_back(module);
    }
    else
    {
        assert(false && "The module is already been added!");
    }

    return module;
}

template<typename _ModuleType>
inline std::shared_ptr<_ModuleType> Application::GetModule() const
{
    auto iter = m_modulesToFind.find(tgon::GetRTTI<_ModuleType>()->GetHashCode());
    if (iter == m_modulesToFind.end())
    {
        return nullptr;
    }

    return std::static_pointer_cast<_ModuleType>(iter->second);
}

} /* namespace tgon */
