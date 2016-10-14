/*
 * Author : Cha Jnho
 * Date : 07/23/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../Core/Object/EventObject.h"
#include "../Engine/Module/Interface/IModule.h"

#include <memory>
#include <algorithm>
#include <map>
#include <boost/variant.hpp>


namespace tgon
{


/* 
 * Static method class 
*/
class GlobalModuleContext :
	public EventObject
{
	/*
	 * Generator
	*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( GlobalModuleContext, EventObject )
	
	/* 
	 * Commands
	*/ 
public:
	static void AddModule( const std::shared_ptr<IModule>& module );

	/* 
	 * Gets
	*/ 
	/*
	 * @param	ModuleTy	Module type that inherited by IModule
	 * @return				Return registered module
	*/
	template <typename ModuleTy>
	static const std::shared_ptr<ModuleTy>& GetModule( );

	/* 
	 * Variables
	*/ 
private:
	/* @note Use on find module */
	static std::map<uintptr_t, std::shared_ptr<IModule>> m_modules;
};


template<typename ModuleTy>
inline const std::shared_ptr<ModuleTy>& GlobalModuleContext::GetModule( )
{
	static_assert( std::is_convertible<ModuleTy*, IModule*>::value, 
		"ModuleTy must be intherited by IModule." );

	auto iter = m_modules.find( ModuleTy::GetHashCode( ));
	if ( m_modules.end != iter )
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}


};
