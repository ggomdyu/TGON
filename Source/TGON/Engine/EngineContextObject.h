/**
 * @filename    EngineContextObject.h
 * @author      ggomdyu
 * @since       07/23/2016
 */

#pragma once
#include <memory>
#include <map>

#include "Module/Interface/IModule.h"
#include "Module/TimeModule.h"

namespace tgon
{

class ModuleContext :
    public object::Object
{
/**
 * @section Generator
 */
public:
    TGON_MAKE_OBJECT_INTERFACE(tgon::ModuleContext)

/**
 * @section Public command method
 */ 
public:
    template <typename ModuleTy,
		      typename = typename std::enable_if<std::is_convertible<ModuleTy*, IModule*>::value>::type>
    static void AddModule();

/**
 * @section Get method
 */
public:
	/**
	 * @param	ModuleTy	Module type that inherited by IModule
	 * @return				Return registered module
	 */
	template <typename ModuleTy,
		      typename = typename std::enable_if<std::is_convertible<ModuleTy*, IModule*>::value>::type>
    static const std::shared_ptr<ModuleTy>& GetModule();

/**
 * @section Private variable
 */ 
private:
	static std::map<uintptr_t, std::shared_ptr<IModule>> m_modules;
    static std::shared_ptr<TimeModule> m_timeModule;
};

template <typename ModuleTy, typename>
inline static void tgon::ModuleContext::AddModule()
{
    //std::lock_guard<std::mutex>( this->GetSystemMutex( ));
    
    auto newModule = std::make_shared<ModuleTy>();

    // Check duplication of module.
    auto iter = m_modules.find(newModule->GetHashCode());
    if (iter == m_modules.end())
    {
        // If the map has no module, then add it.
        m_modules.insert({ newModule->GetHashCode(), newModule });
    }
    else
    {
        // If module does exist, call assert.
        assert(false && "Module duplication occured!");
    }
}

template <>
inline static void ModuleContext::AddModule<TimeModule>()
{
    if (m_timeModule.get())
    {
        assert(false && "m_timeModule already has module you added.");
    }

    m_timeModule = std::make_shared<TimeModule>();
}

template<typename ModuleTy, typename>
inline const std::shared_ptr<ModuleTy>& ModuleContext::GetModule()
{
    auto iter = m_modules.find(ModuleTy::GetTypeInfo().GetHashCode());
    if (m_modules.end() != iter)
    {
        return std::static_pointer_cast<ModuleTy>(iter->second);
    }
	else
	{
		return nullptr;
	}
}

template<>
inline const std::shared_ptr<TimeModule>& ModuleContext::GetModule<TimeModule>()
{
    return m_timeModule;
}

} /* namespace tgon */