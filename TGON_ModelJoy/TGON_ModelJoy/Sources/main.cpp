#include "stdafx.h"


#include "CoreEngine.h"
#include <System\GraphicsSystem.h>
#include <System\WindowSystem.h>
#include <System\TickSystem.h>

using namespace tgon;

int tgMain( int argc, char* argv[] )
{
	CoreEngine::GetInstance( )->RegisterSystem({
		WindowSystem::GetInstance( ),
		GraphicsSystem::GetInstance( ),
		TickSystem::GetInstance( )
	});

	CoreEngine::GetInstance( )->Initialize( );
	CoreEngine::GetInstance( )->FrameMove( );

	return 0;
}