#include "stdafx.h"


#include "CoreEngine.h"
#include "MessageManager.h"
#include "GraphicsSystem.h"

#include "WindowSystem.h"
#include "WindowSystemMessageType.h"

using namespace tgon;

int tgMain( int argc, char* argv[] )
{
	CoreEngine::GetInstance( )->RegisterSystem( WindowSystem::GetInstance( ));
	CoreEngine::GetInstance( )->RegisterSystem( GraphicsSystem::GetInstance( ));
	
	CoreEngine::GetInstance( )->InitializeAllSystems( );

	bool isEventExist = false;

	while ( true )
	{
		isEventExist = WindowSystem::GetInstance( )->PumpWindowEvent( );
		if ( !isEventExist )
		{
			 /* Idle time */
			CoreEngine::GetInstance( )->FrameMove( );
		}
		else
		{
			if ( WindowSystem::GetInstance( )->IsEventOccured( WM_LBUTTONDOWN ))
			{
				MessageBox( NULL, L"WM_LBUTTONDOWN", L"", MB_OK );
				break;
			}

			if ( WindowSystem::GetInstance( )->IsEventOccured( WindowEvent::Destroy ))
			{
				MessageBox( NULL, L"¾ÈµÅ °¡Áö¸¶¤Ð", L"", MB_OK );
				break;
			}

			MessageManager::GetInstance( )->Broadcast(
					SociableMessage( "M", SociableMessageType::ClearAllWindowEvents ));
		}
	}
	return 0;
}