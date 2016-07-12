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
		m_graphics( TGraphics::Make( *this ))
	{
	}

	~TgonModelJoyForm( )
	{
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
	}

private:
	SpTGraphics m_graphics;

};


}