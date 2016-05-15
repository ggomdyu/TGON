#include "PrecompiledHeader.h"

#include <System/TCoreEngine.h>
#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Math/TMath.h>
#include <Window/WindowEvent.h>
#include <Application/TApplication.h>
#include <MessageBox/TMessageBox.h>


using namespace tgon;

int32_t OnEventOccured( TWindow* sender, WindowEvent msg )
{
	switch ( msg )
	{
	case WindowEvent::Create:
		{
		}
		break;

	case WindowEvent::RMouseDown:
		{
			TMessageBox::Show( L"¾Æadgd!!", L"OPOP", TMsgBoxButton::YesNoCancel );
	
		}
		break;

	case WindowEvent::Destroy:
		{
		}
		break;
	}

	return 1;
}


int32_t tgMain( int32_t argc, char* argv[] )
{
	using namespace tgon;
	
	TCoreEngine ce( OnEventOccured );
	ce.Run( );

	return 0;
}