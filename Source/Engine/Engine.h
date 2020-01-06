/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include <vector>

#include "Module.h"
#include "EngineConfig.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    \
    std::unique_ptr<Engine> CreateEngine()\
    {\
        static_assert(std::is_base_of_v<Engine, className>, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
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

/* @section Type */
private:
    using ModuleUnit = size_t;
    using ModuleCache = std::vector<std::shared_ptr<Module>>;

/**@section Constructor */
public:
    explicit Engine(const EngineConfig& enfingConfig) noexcept;

/**@section Destructor */
public:
    virtual ~Engine() = 0;

/**@section Method */
public:
    virtual void Initialize();
    virtual void Destroy();
    virtual void Update();
    template <typename _ModuleType, typename... _ArgTypes>
    std::shared_ptr<_ModuleType> AddModule(_ArgTypes&&... args);
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> FindModule() noexcept;
    template <typename _ModuleType>
    std::shared_ptr<const _ModuleType> FindModule() const noexcept;
    template <typename _ModuleType>
    bool RemoveModule();
    void RemoveAllModule();
    const EngineConfig& GetEngineConfig() const noexcept;

private:
    template <typename _ModuleType>
    ModuleUnit GetModuleUnit() const;

/**@section Variable */
private:
    EngineConfig m_engineConfig;
    mutable ModuleCache m_moduleCache;
    inline static ModuleUnit m_maxModuleUnit;
};
    
template <typename _ModuleType, typename... _ArgTypes>
inline std::shared_ptr<_ModuleType> Engine::AddModule(_ArgTypes&&... args)
{
    auto moduleUnit = GetModuleUnit<_ModuleType>();
    auto module = std::make_shared<_ModuleType>(std::forward<_ArgTypes>(args)...);
    m_moduleCache[moduleUnit] = module;
    
    module->Initialize();
    return module;
}

template <typename _ModuleType>
inline std::shared_ptr<_ModuleType> Engine::FindModule() noexcept
{
    auto moduleUnit = GetModuleUnit<_ModuleType>();
    if (moduleUnit >= m_moduleCache.size() || m_moduleCache[moduleUnit] == nullptr)
    {
        return nullptr;
    }

    return std::static_pointer_cast<_ModuleType>(m_moduleCache[moduleUnit]);
}

template <typename _ModuleType>
inline std::shared_ptr<const _ModuleType> Engine::FindModule() const noexcept
{
    return const_cast<Engine*>(this)->FindModule<_ModuleType>();
}

template<typename _ModuleType>
inline bool Engine::RemoveModule()
{
    auto moduleUnit = GetModuleUnit<_ModuleType>();
    auto& module = m_moduleCache[moduleUnit];
    if (module == nullptr)
    {
        return false;
    }

    module = nullptr;
    return true;
}

template<typename _ModuleType>
inline Engine::ModuleUnit Engine::GetModuleUnit() const
{
    static ModuleUnit moduleUnit = [&]()
    {
        ModuleUnit ret = m_maxModuleUnit;
        m_moduleCache.resize(++m_maxModuleUnit);
        return ret;
    } ();

    return moduleUnit;
}

} /* namespace tgon */
