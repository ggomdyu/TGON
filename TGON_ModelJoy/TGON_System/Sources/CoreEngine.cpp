#include "stdafx.h"
#include "CoreEngine.h"

#include "System\WindowSystem.h"
#include "SociableManager.h"
#include "MessageManager.h"
#include "CoreEngineUtil.h"


void OnFrameExit( )
{
//	tgon::CoreEngine::GetInstance( )->Exit( );
}


tgon::CoreEngine::CoreEngine( )
{
	System::AddEventCallback( WindowEvent::Destroy, OnFrameExit );
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
	for ( const auto& sysElem : systemList )
	{
		/*
			To avoid duplication of element
		*/
		const auto findElem = std::find( m_systemRepo.begin( ), m_systemRepo.end( ), sysElem );
		const auto notExist = m_systemRepo.end( );

		// WindowSystem must be updated passively!! ( because of check idle time )
		if ( sysElem == WindowSystem::GetInstance( ))
			continue;

		if ( findElem == notExist )
		{
			m_systemRepo.push_back( sysElem );
		}
	}
}

void tgon::CoreEngine::FrameMove( )
{
	float elapsedTime = 0;// Time::GetElapsedTime( );

	while ( !m_isLoopExit )
	{
		this->UpdateSystem( elapsedTime );
		this->UpdateManager( elapsedTime );
	}
}

void tgon::CoreEngine::UpdateSystem( float elapsedTime )
{
	GetWindowSystem( )->FrameMove( elapsedTime );

	/*
		Idle time - WindowSystem has no message.
	*/
	const WindowEvent curWndEvent = GetWindowSystem( )->GetWindowEvent( );

	if ( curWndEvent == WindowEvent::None )
	{
		for ( auto& sysElem : m_systemRepo )
		{
			sysElem->FrameMove( elapsedTime );
		}
	}
}


void tgon::CoreEngine::UpdateManager( float elapsedTime )
{
	MessageManager::GetInstance( )->FrameMove( elapsedTime );
	SociableManager::GetInstance( )->FrameMove( elapsedTime );
}