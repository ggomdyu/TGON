#include "stdafx.h"


#include "CoreEngine.h"
#include "CoreUtil.h"
#include <System\GraphicsSystem.h>
#include <System\WindowSystem.h>
#include <System\TickSystem.h>

using namespace tgon;


void OnFrameExit( )
{
	CoreEngine::GetInstance( )->Exit( );
}

int tgMain( int argc, char* argv[] )
{
	CoreEngine::GetInstance( )->RegisterSystem({
		WindowSystem::GetInstance( ),
		GraphicsSystem::GetInstance( ),
		TickSystem::GetInstance( )
	});

	System::RegisterEventCallback( WindowEvent::Destroy, OnFrameExit );
	
	CoreEngine::GetInstance( )->Initialize( );
	CoreEngine::GetInstance( )->FrameMove( );

	return 0;
}