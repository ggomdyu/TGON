/**
 * filename Engine.h
 * Author : Cha Jnho
 * since    07/23/2016
 */

#pragma once
#include "EngineContextObject.h"


namespace tgon
{

class GameApplication;

class TGON_API Engine :
	public ModuleContext
{
/**
 * Generator
 */ 
public:
	TGON_GENERATE_OBJECT_INTERFACE( Engine )

/**
 * Ctor/Dtor
 */ 
public:
	Engine( );
	virtual ~Engine( ) = default;

/**
 * Commands
 */ 
public:
	int32_t Execute( int argc, char** argv );

/**
 * Private methods
 */ 
private:
	void AddEssentialModules( );

	void UpdateModules( );

/** 
 * Private variables
 */ 
private:
	std::shared_ptr<GameApplication> m_gameApplication;
	
    std::vector<IModule*> m_modulesForFastIter;

};

} /*namespace tgon*/