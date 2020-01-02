/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include <vector>
#include <mutex>

#include "Module.h"

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

/* @section Type */
private:
    using ModuleUnit = size_t;
    using ModuleCache = std::vector<std::shared_ptr<Module>>;

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

private:
    template <typename _ModuleType>
    ModuleUnit GetModuleUnit() const;

/**@section Variable */
private:
    std::mutex m_mutex;
    mutable ModuleCache m_moduleCache;
    inline static ModuleUnit m_maxModuleUnit;
};
    
template <typename _ModuleType, typename... _ArgTypes>
inline std::shared_ptr<_ModuleType> Engine::AddModule(_ArgTypes&&... args)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto module = std::make_shared<_ModuleType>(std::forward<_ArgTypes>(args)...);
    auto moduleUnit = GetModuleUnit<_ModuleType>();
    m_moduleCache[moduleUnit] = module;
    
    return module;
}

template <typename _ModuleType>
inline std::shared_ptr<_ModuleType> Engine::FindModule() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);

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
inline Engine::ModuleUnit Engine::GetModuleUnit() const
{
    static ModuleUnit moduleUnit = [&]()
    {
        ModuleUnit moduleUnit = m_maxModuleUnit;
        m_moduleCache.resize(++m_maxModuleUnit);
        return moduleUnit;
    } ();

    return moduleUnit;
}

} /* namespace tgon */
