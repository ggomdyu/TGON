#include "CoreEngine.h"

#include "MessageManager.h"
#include <System\TickSystem.h>


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


void  tgon::CoreEngine::Pause( )
{
	m_isLoopActivated = false; 
}

void  tgon::CoreEngine::Resume( )
{
	m_isLoopActivated = true;
}

void  tgon::CoreEngine::Exit( )
{
	m_isLoopExit = true;
}


void tgon::CoreEngine::RegisterSystem( const std::initializer_list<ISystem*>& systemList )
{
	for ( auto& system : systemList )
	{
		m_systemRepo.push_back( system );
	}
}

void tgon::CoreEngine::FrameMove( )
{
	float elapsedTime = 0.0f;// = Time::GetElapsedTime( );

	while ( !m_isLoopExit )
	{
		this->UpdateSystem( elapsedTime );
		this->UpdateManager( elapsedTime );
	}
}


void tgon::CoreEngine::UpdateSystem( float elapsedTime )
{ 
	for ( auto& system : m_systemRepo )
	{
		system->FrameMove( elapsedTime );
	}
}


void tgon::CoreEngine::UpdateManager( float elapsedTime )
{
	MessageManager::GetInstance( )->FrameMove( elapsedTime );
	SociableManager::GetInstance( )->FrameMove( elapsedTime );
}