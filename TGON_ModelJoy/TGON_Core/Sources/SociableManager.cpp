//#include "stdafx.h"
#include "SociableManager.h"


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


void tgon::SociableManager::DispatchMessage( _In_ const SociableMessage& msg )
{
	const auto iter = m_sociableMap.find( msg.GetAccepterName( ));

	if ( iter != m_sociableMap.end( )) {
		iter->second->RecvMessage( msg );
	}
}