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
	int loopc = 0;
	for ( auto iter = m_msgRepo.begin( ); iter != m_msgRepo.end( ); ++iter )
	{
		++loopc;

		iter->SetDelayTime( iter->GetDelayTime( ) - elapsedTime );

		if ( iter->GetDelayTime( ) <= 0.0f )
		{
			SociableManager::GetInstance( )->DispatchMessage( *iter );
			//iter = m_msgRepo.erase( iter );
		}
	}
}