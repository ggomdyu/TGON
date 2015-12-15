#include "CoreEngine.h"

#include "MessageManager.h"
#include "TickSystem.h"


tgon::CoreEngine::CoreEngine( )
{
}


tgon::CoreEngine::~CoreEngine( )
{
}


void tgon::CoreEngine::Initialize( )
{
	for ( auto& system : m_systemRepo )
	{
		system->Initialize( );
	}
}


void tgon::CoreEngine::RegisterSystem( const std::initializer_list<ISystem*>& systemList )
{
	//for ( auto& system : systemList )
	//{
	//	m_systemRepo.push_back( system );
	//}
}


void tgon::CoreEngine::FrameMove( )
{
	const float elapsedTime = GetElapsedTime( );

	/*while ( !m_isLoopExit )
	{
		this->FrameMoveAllSystems( elapsedTime );
		this->FrameMoveAllManagers( elapsedTime );
	}*/
}


void tgon::CoreEngine::FrameMoveAllSystems( float elapsedTime )
{ 
	for ( auto& system : m_systemRepo )
	{
		system->FrameMove( elapsedTime );
	}
}


void tgon::CoreEngine::FrameMoveAllManagers( float elapsedTime )
{ 
	MessageManager::GetInstance( )->FrameMove( elapsedTime );
	SociableManager::GetInstance( )->FrameMove( elapsedTime );
}