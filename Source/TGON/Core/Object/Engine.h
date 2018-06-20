/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include "Module/TimeModule.h"
#include "Module/InputModule.h"
#include "CoreObject.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    \
    std::unique_ptr<Engine> MakeEngine()\
    {\
        static_assert(std::is_base_of<Engine, className>::value, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return std::make_unique<className>();\
    }\
    \
    } /* namespace tgon */

namespace tgon
{

class IModule;
struct WindowStyle;
    
class TGON_API Engine :
    public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(Engine);

/* @section Public constructor */
public:
    Engine();
    
/* @section Public destructor */
public:
    virtual ~Engine() = 0;
    
/* @section Public method */
public:
    virtual void Update();
    
    /**
     * @brief               Inserts a module to manage.
     * @param [in] args     Parameters of the _ModuleType constructor.
     */
    template <typename _ModuleType, typename... _ArgTypes>
    void AddModule(_ArgTypes&&... args);
    
    /**
     * @brief               Removes the managed module.
     * @tparam _ModuleType  The type of module what you want to remove.
     */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    bool RemoveModule();

    /* @brief   Returns a module that managed by Application. */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    std::shared_ptr<const _ModuleType> GetModule() const noexcept;

    /* @brief   Returns a module that managed by Application. */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    std::shared_ptr<_ModuleType> GetModule() noexcept;
    
/* @section Public event handler */
public:
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    
/* @section Private method */
private:
    /**
     * @brief               Inserts a module to manage.
     * @param [in] module   The module what you want to insert.
     */
    void AddModule(std::shared_ptr<IModule> module);
    
    /**
     * @brief               Returns a module that managed by Application.
     * @param [in] moduleId The unique id of Module what you want to get.
     * @return              Returns a pointer to module if successful, nullptr otherwise.
     */
    std::shared_ptr<const IModule> GetModule(size_t moduleId) const;

    /**
     * @brief               Returns a module that managed by Application.
     * @param [in] moduleId The unique id of Module what you want to get.
     * @return              Returns a pointer to module if successful, nullptr otherwise.
     */
    bool RemoveModule(size_t moduleId);

/* @section Private variable */
private:
    std::shared_ptr<TimeModule> m_timeModule;

    std::vector<std::shared_ptr<IModule>> m_modules;
};

template <typename _ModuleType, typename ..._ArgTypes>
inline void Engine::AddModule(_ArgTypes&&... args)
{
    this->AddModule(std::make_shared<_ModuleType>(std::forward<_ArgTypes>(args)...));
}

template <>
inline void Engine::AddModule<TimeModule>()
{
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline std::shared_ptr<const _ModuleType> Engine::GetModule() const noexcept
{
    return const_cast<Engine*>(this)->GetModule<_ModuleType>();
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline std::shared_ptr<_ModuleType> Engine::GetModule() noexcept
{
    return std::static_pointer_cast<_ModuleType>(this->GetModule(tgon::GetRTTI<_ModuleType>()->GetHashCode()));
}

template <>
inline std::shared_ptr<const TimeModule> Engine::GetModule<TimeModule>() const  noexcept
{
    return m_timeModule;
}

template <>
inline std::shared_ptr<TimeModule> Engine::GetModule<TimeModule>() noexcept
{
    return m_timeModule;
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline bool Engine::RemoveModule()
{
    return this->RemoveModule(tgon::GetRTTI<_ModuleType>()->GetHashCode());
}
    
} /* namespace tgon */
