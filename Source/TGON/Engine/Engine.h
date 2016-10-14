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
	public GlobalModuleContext
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	Engine( );
	virtual ~Engine( ) = default;

	/* 
	 * Generator
	*/ 
public:
	TGON_GENERATE_OBJECT_INTERFACE( Engine, GlobalModuleContext )

	/* 
	 * Commands
	*/ 
public:
	int32_t Execute( int argc, char** argv );

	/* 
	 * Event handlers
	*/ 
private:
	void OnModuleAdded( IModule* module );

	/* 
	 * Internal works
	*/ 
private:
	/* @note Create and add modules to m_modules */
	void AddDefaultModulesToRepo( );
	void UpdateModules( );

	/* 
	 * Variables
	*/ 
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