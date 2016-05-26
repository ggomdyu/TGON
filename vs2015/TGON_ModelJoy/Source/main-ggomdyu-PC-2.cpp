#include "PrecompiledHeader.h"

#include <System/TCoreEngine.h>
#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Core/Math/TMath.h>
#include <Window/WindowEvent.h>
#include <Window/TWindow.h>
#include <Window/WindowStyle.h>
#include <Application/TApplication.h>
#include <MessageBox/TMessageBox.h>
#include <System/WindowSystem.h>


using namespace tgon;

class MyWindowForm : public TWindow
{
public:
	MyWindowForm( ) :
		TWindow( this->MakeWindowStyle( ), true ) {}

	virtual void OnIdle( ) override
	{
	}

private:
	WindowStyle MakeWindowStyle( ) const
	{
		return WindowStyle::ParseFromXML( L"WindowStyle.xml" );
	}
};


#include <tgLib/auto_cast.h>

int32_t tgMain( int32_t argc, char* argv[] )
{
	using namespace tgon;

	//TCoreEngine ce( OnEventOccured );
	//ce.Run( );

	MyWindowForm window;
	window.Make( );
	
	TApplication::Run( window );

	return 0;
}