//#include "stdafx.h"
#include "MessageManager.h"

#include "SociableManager.h"


Implement_Singleton_Instance( tgon::MessageManager )


tgon::MessageManager::MessageManager( )
{
}


tgon::MessageManager::~MessageManager( )
{
}


void tgon::MessageManager::FrameMove( )
{
	for ( auto iter( m_msgRepo.begin( )); iter != m_msgRepo.end( ); ++iter )
	{
		iter->SetDelayTime( iter->GetDelayTime( ) - 0.01f );

		if ( iter->GetDelayTime( ) <= 0.0f )
		{
			SociableManager::GetInstance( )->DispatchMessage( *iter );
			m_msgRepo.erase( iter );
		}
	}
}