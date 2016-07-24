#pragma once

#include <Window/TWindow.h>
#include <Graphics/TGraphics.h>
#include <Console/TConsole.h>
#include <Screen/TScreen.h>
#include <Object/TObject.h>
#include <Object/TEventSubject.h>


namespace tgon
{



class TgonModelJoyForm :
	public TWindow
{
public:
	TgonModelJoyForm( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" )),
		m_graphics( TGraphics::Make( this ))
	{
		m_graphics->SetClearColor( 0x0000ff );
	}

	~TgonModelJoyForm( )
	{
	}

	/*virtual void OnIdle( ) override
	{
		m_graphics->Clear( );
		m_graphics->BeginScene( );



		m_graphics->EndScene( );
		m_graphics->Present( );
	}*/


private:
	SpTGraphics m_graphics;

};


}