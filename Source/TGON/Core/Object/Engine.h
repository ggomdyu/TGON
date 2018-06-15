/**
 * @filename    Engine.h
 * @author      ggomdyu
 * @since       06/11/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/WindowType.h"
#include "Module/IModule.h"

#include "Object.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    \
    Engine* MakeEngine()\
    {\
        static_assert(std::is_base_of<Engine, className>::value, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return new className();\
    }\
    \
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
     * @param [in] module   The module what you want to manage.
     */
    void AddModule(IModule* module);
    
    /**
     * @brief               Removes managed module.
     * @tparam _ModuleType  The type of module what you want to remove.
     */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    void RemoveModule();

    /* @brief               Returns a module that managed by Application. */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    std::shared_ptr<_ModuleType> GetModule() const;
    
/* @section Public event handler */
public:
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    
/* @section Private method */
private:
    std::shared_ptr<IModule> GetModule(size_t moduleId) const;

    bool RemoveModule(size_t moduleId);

/* @section Private variable */
private:
    std::vector<std::shared_ptr<IModule>> m_modules;
};

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline std::shared_ptr<_ModuleType> Engine::GetModule() const
{
    return std::static_pointer_cast<_ModuleType>(this->GetModule(tgon::GetRTTI<_ModuleType>()->GetHashCode()));
}

template<typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline void Engine::RemoveModule()
{
    return this->RemoveModule(tgon::GetRTTI<_ModuleType>()->GetHashCode());
}
    
} /* namespace tgon */
