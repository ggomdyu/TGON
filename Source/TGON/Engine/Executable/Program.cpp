#include "PrecompiledHeader.h"
#include "Program.h"


#include "../../Platform/Window/TWindow.h"
#include "../../Platform/Main/TMain.h"
#include "../../Platform/Application/TApplication.h"

#include <SDL.h>


TGON_REGISTER_MAINAPP( tgon::Program )

#include <Window/Abstract/AbstractWindowEventHandler.h>
class Win :
	public tgon::AbstractWindowEventHandler
{
public:
	virtual bool OnDestroy( ) override
	{
		gameIsDone = true;
		return true;
	}

public:
	bool gameIsDone = false;
};

int32_t tgon::Program::Main( )
{
	// Make window as default style
	auto window = TWindow::Make( WindowStyle::DefaultStyle );

	auto evh = std::make_shared<Win>( );

	window->EnableGlobalMouseFocus( true );
	window->SetEventHandler( evh );

	while ( !evh->gameIsDone )
	{
		if ( !TApplication::Get()->PumpEvent( ))
		{
		}
	}


	return 0; 
	
	//TApplication::Run( *window.get( ) );
}