//#include "stdafx.h"
#include "SociableManager.h"
#include <cassert>

Implement_Singleton_Instance( tgon::SociableManager )

tgon::SociableManager::SociableManager( )
{
}


tgon::SociableManager::~SociableManager( )
{
}

void tgon::SociableManager::FrameMove( float elapsedTime )
{
}

void tgon::SociableManager::DispatchMessage( _In_ const CommMessage& msg )
{
	const auto iter = m_sociableMap.find( msg.GetAccepterType( ));
	if ( iter != m_sociableMap.end( ))
	{
		//iter->second->RecvMessage( msg );
	}
}