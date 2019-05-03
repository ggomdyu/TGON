/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include "Core/Object/CoreObject.h"

#include "Module/TimeModule.h"
#include "Module/InputModule.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    \
    std::unique_ptr<Engine> CreateEngine()\
    {\
        static_assert(std::is_base_of<Engine, className>::value, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return std::make_unique<className>();\
    }\
    \
    } /* namespace tgon */

namespace tgon
{

class TGON_API Engine :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(Engine);

/**@section Protected constructor */
protected:
    Engine();

/**@section Public destructor */
public:
    virtual ~Engine() = 0;
    
/**@section Public method */
public:
    /**
     * @brief   Updates the Engine.
     * @detail  When this function has invoked, all registered modules are updated.
     */
    virtual void Update();
    
    /**
     * @brief   Registers a module to manage through this engine.
     * @param [in] args     Parameters of the _ModuleType constructor.
     */
    template <typename _ModuleType, typename... _ArgTypes>
    std::shared_ptr<_ModuleType> RegisterModule(_ArgTypes&&... args);

    /**
     * @brief   Unregisters a module managed by this engine.
     * @tparam _ModuleType  The type of module to remove.
     */
    template <typename _ModuleType>
    bool UnregisterModule();

    /**@brief   Returns a module managed by this engine. */
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> FindModule() noexcept;

    /**@brief   Returns a module managed by this engine. */
    template <typename _ModuleType>
    std::shared_ptr<const _ModuleType> FindModule() const noexcept;
    
/**@section Public event handler */
public:
    virtual void OnLaunch();
    virtual void OnTerminate();

/**@section Private method */
private:
    /**
     * @brief   Registers a module to manage through this engine.
     * @param [in] module   The module to insert.
     */
    void RegisterModule(const std::shared_ptr<IModule>& module);
    
    /**
     * @brief   Returns a module that managed by Application.
     * @param [in] moduleId     The unique id of the module to get.
     * @return  Returns a pointer to module if successful, nullptr otherwise.
     */
    std::shared_ptr<IModule> FindModule(size_t moduleId);

    /**
     * @brief   Returns a module that managed by Application.
     * @param [in] moduleId     The unique id of the module to get.
     * @return  Returns a pointer to module if successful, nullptr otherwise.
     */
    bool UnregisterModule(size_t moduleId);

/**@section Private variable */
private:
    std::shared_ptr<TimeModule> m_timeModule;

    std::vector<std::shared_ptr<IModule>> m_modules;
};
    
template <>
inline std::shared_ptr<TimeModule> Engine::FindModule<TimeModule>() noexcept
{
    return m_timeModule;
}

template <>
inline std::shared_ptr<const TimeModule> Engine::FindModule<TimeModule>() const noexcept
{
    return m_timeModule;
}
    
template <typename _ModuleType, typename... _ArgTypes>
inline std::shared_ptr<_ModuleType> Engine::RegisterModule(_ArgTypes&&... args)
{
    auto module = std::make_shared<_ModuleType>(std::forward<_ArgTypes>(args)...);
    
    this->RegisterModule(module);
    return module;
}
    
template <typename _ModuleType>
inline bool Engine::UnregisterModule()
{
    return this->UnregisterModule(tgon::GetRTTI<_ModuleType>()->GetHashCode());
}

template <typename _ModuleType>
inline std::shared_ptr<_ModuleType> Engine::FindModule() noexcept
{
    return std::static_pointer_cast<_ModuleType>(this->FindModule(tgon::GetRTTI<_ModuleType>()->GetHashCode()));
}

template <typename _ModuleType>
inline std::shared_ptr<const _ModuleType> Engine::FindModule() const noexcept
{
    return const_cast<Engine*>(this)->FindModule<_ModuleType>();
}
    
} /* namespace tgon */
