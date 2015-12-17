//#include "stdafx.h"
#include "MessageManager.h"

#include "SociableManager.h"


tgon::MessageManager::MessageManager( )
{
}


tgon::MessageManager::~MessageManager( )
{
}


void tgon::MessageManager::FrameMove( float elapsedTime )
{
	for ( auto iter = m_msgRepo.begin( ); iter != m_msgRepo.end( ); ++iter )
	{
		iter->SetDelayTime( iter->GetDelayTime( ) - elapsedTime );

		if ( iter->GetDelayTime( ) <= 0.0f )
		{
			SociableManager::GetInstance( )->DispatchMessage( *iter );
			//iter = m_msgRepo.erase( iter );
		}
	}
}