#include "PrecompiledHeader.h"

#include <System/EngineLoop.h>
#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Math/TMath.h>
#include <Window/WindowEvent.h>

#include "Object/TObject.h"


using namespace tgon;


int32_t tgMsgProc( tgon::TWindow* window, tgon::WindowEvent msg )
{
	switch ( msg )
	{
	case WindowEvent::Create:
		{
		}
		break;
	}

	return 1;
}

#include "Math/Vector3D.h"


int32_t tgMain( int32_t argc, char* argv[] )
{
	using namespace tgon;
	


	EngineLoop el( tgMsgProc );
	el.Run( );

	return 0;
}