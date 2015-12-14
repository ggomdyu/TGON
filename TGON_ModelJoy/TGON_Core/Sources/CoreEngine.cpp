#include "CoreEngine.h"

#include "MessageManager.h"
#include "WindowSystem.h"


tgon::CoreEngine::CoreEngine( )
{

}


tgon::CoreEngine::~CoreEngine( )
{
}

void tgon::CoreEngine::InitializeAllSystems( )
{
	for ( auto& system : m_systemRepo ) {
		system->Initialize( );
	}
}

void tgon::CoreEngine::RegisterSystem( _In_ ISystem* system, ... )
{
    m_systemRepo.push_back( system );
}



	/*va_list vList;
	va_start( vList, system );

	while ( system )
	{
		m_systemRepo.push_back( system );
		++system;
	}

	va_end( vList );*/
/*
 
    */


void tgon::CoreEngine::FrameMove( )
{ 
	this->FrameMoveAllManagers( );
	this->FrameMoveAllSystems( );
}

void tgon::CoreEngine::FrameMoveAllSystems( )
{ 
	for ( auto& system : m_systemRepo ) {
		system->FrameMove( );
	}
}

void tgon::CoreEngine::FrameMoveAllManagers( )
{ 
	for ( auto& system : m_systemRepo ) {
		system->FrameMove( );
	}
}