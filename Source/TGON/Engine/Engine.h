/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

#include "Core/Object.h"

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

/**@section Destructor */
public:
    virtual ~Engine() = 0;
    
/**@section Method */
public:
    virtual void Initialize();
    virtual void Update();
    template <typename _ModuleType, typename... _ArgTypes>
    std::shared_ptr<_ModuleType> AddModule(_ArgTypes&&... args);
    template <typename _ModuleType>
    std::shared_ptr<_ModuleType> FindModule() noexcept;
    template <typename _ModuleType>
    std::shared_ptr<const _ModuleType> FindModule() const noexcept;
    template <typename _ModuleType>
    bool RemoveModule();

/**@section Variable */
private:
    std::vector<std::shared_ptr<Module>> m_modules;
    std::unordered_map<size_t, std::shared_ptr<Module>> m_moduleDict;
};
    
template <typename _ModuleType, typename... _ArgTypes>
inline std::shared_ptr<_ModuleType> Engine::AddModule(_ArgTypes&&... args)
{
    auto module = std::make_shared<_ModuleType>(std::forward<_ArgTypes>(args)...);
    
    m_modules.push_back(module);
    m_moduleDict.emplace(tgon::GetRTTI<_ModuleType>()->GetHashCode(), module);
    
    return module;
}

template <typename _ModuleType>
inline std::shared_ptr<_ModuleType> Engine::FindModule() noexcept
{
    auto iter = m_moduleDict.find(tgon::GetRTTI<_ModuleType>()->GetHashCode());
    if (iter == m_moduleDict.end())
    {
        return nullptr;
    }
    
    return std::static_pointer_cast<_ModuleType>(iter->second);
}

template <typename _ModuleType>
inline std::shared_ptr<const _ModuleType> Engine::FindModule() const noexcept
{
    return const_cast<Engine*>(this)->FindModule<_ModuleType>();
}

template <typename _ModuleType>
inline bool Engine::RemoveModule()
{
    // Remove module in unordered_map.
    auto moduleHashCode = tgon::GetRTTI<_ModuleType>()->GetHashCode();
    auto dictIter = m_moduleDict.find(moduleHashCode);
    if (dictIter == m_moduleDict.end())
    {
        return false;
    }
    
    m_moduleDict.erase(dictIter);
    
    auto vecIter = std::find_if(m_modules.begin(), m_modules.end(), [&](const std::shared_ptr<Module>& module)
    {
        return moduleHashCode == module->GetRTTI()->GetHashCode();
    });
    if (vecIter != m_modules.end())
    {
        m_modules.erase(vecIter);
    }
    
    return true;
}

} /* namespace tgon */
