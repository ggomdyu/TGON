#include "CoreEngine.h"
#include "stdafx.h"
#include "CoreEngine.h"

#include "SociableManager.h"
#include "MessageManager.h"
#include "CoreEngineUtil.h"


using namespace tgon::Window;


namespace tgon {
namespace CoreEngine {


Window::SpTWindow		g_pWnd;
std::vector<ISystem*>	m_systemRepo;


void RegisterSystem( const std::initializer_list<ISystem*>& systemList )
{
	for ( const auto& sysElem : systemList )
	{
		/*
			To avoid duplication of element
		*/
		const auto findElem = std::find( m_systemRepo.begin( ), m_systemRepo.end( ), sysElem );
		const auto notExistElem = m_systemRepo.end( );

		if ( findElem == notExistElem ) {
			m_systemRepo.push_back( sysElem );
		}
	}
}

void RunSystem( float elapsedTime )
{
	for ( auto& sysElem : m_systemRepo )
		sysElem->FrameMove( elapsedTime );
}

void RunManager( float elapsedTime )
{
	MessageManager::GetInstance( )->FrameMove( elapsedTime );
	SociableManager::GetInstance( )->FrameMove( elapsedTime );
}

}
}


void tgon::CoreEngine::Setup( const SpTWindow& pWnd )
{
	g_pWnd = pWnd;
}

void tgon::CoreEngine::Setup(	const SpTWindow& pWnd,
										const std::initializer_list<ISystem*>& systemList )
{
	CoreEngine::Setup( pWnd );
	CoreEngine::RegisterSystem( systemList );
}


const SpTWindow& tgon::CoreEngine::GetWindow( )
{
	return g_pWnd;
}


void tgon::CoreEngine::Run( )
{
	float elapsedTime = 0;// Time::GetElapsedTime( );GetTickSystem( )->GetElapsedTime( );

	CoreEngine::RunSystem( elapsedTime );
	CoreEngine::RunManager( elapsedTime );
}


void tgon::CoreEngine::DispatchEvent( _Out_ WindowEvent* outGlobalEvent )
{
#ifdef PLATFORM_WINDOWS_OS

	MSG msg;
	BOOL isMsgExist = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );

	if ( isMsgExist )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
	*outGlobalEvent = msg.message;

#endif
}