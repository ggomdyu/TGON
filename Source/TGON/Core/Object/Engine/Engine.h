/**
 * @filename    Engine.h
 * @author      ggomdyu
 * @since       06/11/2018
 * @brief       Define class which becomes the base of all objects.
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "../Module/IModule.h"
#include "../Object.h"

#include "EngineFwd.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    std::unique_ptr<Engine> MakeEngine()\
    {\
        static_assert(std::is_base_of<Engine, className>::value, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return std::make_unique<className>();\
    }\
    } /* namespace tgon */

namespace tgon
{
    
class TGON_API Engine :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(Engine);

/* @section Public method */
public:
    virtual void Update();
    
    virtual WindowStyle GetRootWindowStyle() const noexcept;
    
    /**
     * @brief               Inserts a module to manage.
     * @param [in] args     The constructor parameter set of _ModuleType class.
     */
    template <typename _ModuleType, typename... _Args>
    std::shared_ptr<_ModuleType> AddModule(_Args&&... args);
    
    /**
     * @brief               Inserts a module to manage.
     * @param [in] module   The module what you want to manage.
     */
    void AddModule(const std::shared_ptr<IModule>& module);
    
    /* @brief               Returns a module that managed by Application. */
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> GetModule() const;
    
/* @section Public event handler */
public:
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    
/* @section Private variable */
private:
    std::vector<std::shared_ptr<IModule>> m_modulesToIter;
    std::map<size_t, std::shared_ptr<IModule>> m_modulesToFind;
};

template<typename _ModuleType, typename ..._Args>
inline std::shared_ptr<_ModuleType> Engine::AddModule(_Args&& ...args)
{
    auto module = std::make_shared<_ModuleType>(std::forward<_Args>(args)...);
    
    auto pair = m_modulesToFind.insert({ module->GetRTTI()->GetHashCode(), module });
    if (pair.second == true)
    {
        m_modulesToIter.push_back(module);
    }
    else
    {
        assert(false && "The module is already been added.");
    }
    
    return module;
}

template<typename _ModuleType>
inline std::shared_ptr<_ModuleType> Engine::GetModule() const
{
    auto iter = m_modulesToFind.find(tgon::GetRTTI<_ModuleType>()->GetHashCode());
    if (iter == m_modulesToFind.end())
    {
        return nullptr;
    }
    
    return std::static_pointer_cast<_ModuleType>(iter->second);
}
    
} /* namespace tgon */
