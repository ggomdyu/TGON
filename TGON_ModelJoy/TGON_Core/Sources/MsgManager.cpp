//#include "stdafx.h"
#include "MsgManager.h"

#include "SociableManager.h"


Implement_Singleton_Instance( tgon::MsgManager )


tgon::MsgManager::MsgManager( )
{
}


tgon::MsgManager::~MsgManager( )
{
}


void tgon::MsgManager::FrameMove( )
{
	for ( auto iter( m_msgRepo.begin( )); iter != m_msgRepo.end( ); ++iter )
	{
		iter->SetDelayTime( iter->GetDelayTime( ) - 0.01f );

		if ( iter->GetDelayTime( ) <= 0.0f ) {
			SociableManager::GetInstance( )->DispatchMessage( *iter );
			m_msgRepo.erase( iter );
		}
	}
}