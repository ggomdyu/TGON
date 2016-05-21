#include "PrecompiledHeader.h"

#include <System/TCoreEngine.h>
#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Core/Math/TMath.h>
#include <Window/WindowEvent.h>
#include <Application/TApplication.h>
#include <MessageBox/TMessageBox.h>


using namespace tgon;

int32_t OnEventOccured( TWindow* sender, WindowEvent msg )
{
	switch ( msg )
	{
	case WindowEvent::kCreate:
		{
		}
		break;

	case WindowEvent::kRMouseDown:
		{
//			TMessageBox::Show( L"¾Æadgd!!", L"OPOP", TMsgBoxButton::YesNoCancel );
	
		}
		break;

	case WindowEvent::kDestroy:
		{
		}
		break;
	}

	return 1;
}

#include <Application\TApplication.h>


int32_t tgMain( int32_t argc, char* argv[] )
{
	using namespace tgon;

	TCoreEngine ce( OnEventOccured );
	ce.Run( );

	return 0;
}