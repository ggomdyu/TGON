/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include <memory>
#include <vector>

#include "Core/Object.h"

#include "TimeModule.h"
#include "AudioModule.h"

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

class Engine :
    public Object
{
public:
    TGON_DECLARE_RTTI(Engine)

/**@section Destructor */
public:
    virtual ~Engine() = 0;
    
/**@section Method */
public:
    template <typename _ModuleType, typename... _ArgTypes>
    std::shared_ptr<_ModuleType> RegisterModule(_ArgTypes&&... args);
    template <typename _ModuleType>
    bool UnregisterModule();
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> FindModule() noexcept;
    template <typename _ModuleType>
    std::shared_ptr<const _ModuleType> FindModule() const noexcept;
    virtual void Update();
    
/**@section Event handler */
public:
    virtual void OnLaunch();
    virtual void OnTerminate();

/**@section Method */
private:
    void RegisterModule(const std::shared_ptr<Module>& module);
    bool UnregisterModule(size_t moduleId);
    std::shared_ptr<Module> FindModule(size_t moduleId);

/**@section Variable */
private:
    std::shared_ptr<TimeModule> m_timeModule;
    std::shared_ptr<AudioModule> m_audioModule;
    std::vector<std::shared_ptr<Module>> m_modules;
};
    
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
    return const_cast<decltype(this)>(this)->FindModule<_ModuleType>();
}
    
} /* namespace tgon */
