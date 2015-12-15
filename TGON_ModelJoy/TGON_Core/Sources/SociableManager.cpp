//#include "stdafx.h"
#include "SociableManager.h"


tgon::SociableManager::SociableManager( )
{
}


tgon::SociableManager::~SociableManager( )
{
}


void tgon::SociableManager::FrameMove( float elapsedTime )
{
}


void tgon::SociableManager::RegisterMember( ISociable* member )
{
	m_sociableMap.insert( std::make_pair( member->GetKey( ), member ));
}

void tgon::SociableManager::DispatchMessage( _In_ const SociableMessage& msg )
{
	const auto iter = m_sociableMap.find( msg.GetAccepterKey( ));

	if ( iter != m_sociableMap.end( ))
	{
		iter->second->RecvMessage( msg );
	}
}