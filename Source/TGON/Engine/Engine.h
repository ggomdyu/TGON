/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "EngineContextObject.h"


namespace tgon
{


class GameApplication;

class TGON_API Engine :
	public ModuleContext
{
	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( Engine, ModuleContext )

	// 
	// Commands
	// 
public:
	int32_t Execute( int argc, char** argv );

	// 
	// Event handlers
	// 
private:
	void OnModuleAdded( IModule* module );

	// 
	// Ctor/Dtor
	// 
public:
	Engine( );
	virtual ~Engine( ) = default;

	// 
	// Internal works
	// 
private:
	/* @note Create and add modules to m_modules */
	void AddDefaultModulesToRepo( );
	void UpdateModules( );

	// 
	// Private variables
	// 
private:
	std::shared_ptr<GameApplication> m_gameApplication;
	std::vector<IModule*> m_modulesForFastIter;
};


inline void tgon::Engine::UpdateModules( )
{
	for ( auto module : m_modulesForFastIter )
	{
		module->Update( );
	}
}


} /*namespace tgon*/