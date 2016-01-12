#include "stdafx.h"


#include "CoreEngine.h"
#include "CoreEngineUtil.h"

#include <System\GraphicsSystem.h>
#include <System\WindowSystem.h>
#include <System\TickSystem.h>


using namespace tgon;


void OnFrameLoseFocus( )
{
	
}


int tgMain( int argc, char* argv[] )
{
	/*
		Register system
	*/
	CoreEngine::GetInstance( )->RegisterSystem({
		WindowSystem::GetInstance( ),
		GraphicsSystem::GetInstance( ),
		TickSystem::GetInstance( )
	});
	

	System::AddEventCallback( WindowEvent::LoseFocus, OnFrameLoseFocus );


	CoreEngine::GetInstance( )->Initialize( );
	CoreEngine::GetInstance( )->FrameMove( );

	return 0;
}