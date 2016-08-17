/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/Config/Build.h"

#include "../../Core/Object/TEventSubject.h"
#include "../../Engine/Module/Interface/IModule.h"


namespace tgon
{


class TGON_API TEngine :
	public TEventSubject
{
/*
	Commands
*/
public:
	int32_t Execute( int argc, char** argv );


	//
	// @param module
	//
	void AddModule( const std::shared_ptr<IModule>& module );

/*
	Gets
*/
	//
	// @return registered module by template argument
	//
	template <typename ModuleTy>
	const std::shared_ptr<ModuleTy>& GetModule( );

/*
	Cons/Destructor
*/
public:
	TEngine( );

	virtual ~TEngine( ) = default;


/*
	Internal works
*/
private:
	//
	// @note Create and add modules to m_modules
	//
	void SetupModules( );
	
	void UpdateModules( );

	void WowCPAR( ) {};

	/*
		Private variables
	*/
private:
	//
	// @note Game application
	//
	std::shared_ptr<class TGameApplication> m_gameApp;

	//
	// @note Use on finding module
	//
	std::map<uintptr_t, std::shared_ptr<IModule>> m_modules;

	//
	// @note For fast iterating than std::map
	//
	std::vector<std::shared_ptr<IModule>> m_modulesForUpdate;
};


inline void tgon::TEngine::UpdateModules( )
{
	for ( auto module : m_modulesForUpdate )
	{
		module->Update( );
	}
}

template<typename ModuleTy>
inline const std::shared_ptr<ModuleTy>& TEngine::GetModule( )
{
	static_assert( std::is_convertible<ModuleTy*, IModule*>::value,
		"Working good?" );

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
