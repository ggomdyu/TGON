#include "stdafx.h"


#include "CoreEngine.h"
#include "WindowSystem.h"

using namespace tgon;

int tgMain( int argc, char* argv[] )
{
	CoreEngine::GetInstance( )->RegisterSystem( WindowSystem::GetInstance( ));
	CoreEngine::GetInstance( )->InitializeAllSystems( );

	bool isEventExist = false;

	while ( true )
	{
		isEventExist = WindowSystem::GetInstance( )->PumpWindowEvent( );
		if ( !isEventExist ) /* Idle time */
		{
			CoreEngine::GetInstance( )->FrameMoveAllSystems( );
		}
		else
		{
			if ( WindowSystem::GetInstance( )->IsEventOccured( WindowEvent::Destroy ))
			{
				MessageBox( NULL, L"¾ÈµÅ °¡Áö¸¶¤Ð", L"", MB_OK );
				break;
			}

			WindowSystem::GetInstance( )->ClearAllWindowEvents( );
		}
	}
	return 0;
}