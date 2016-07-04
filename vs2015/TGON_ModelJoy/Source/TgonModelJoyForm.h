#pragma once

#include <Window/TWindow.h>
#include <Window/WindowStyle.h>
#include <Graphics/TGraphics.h>
#include <Console/TConsole.h>
#include <Graphics/Direct3D9/D3D9Error.h>


namespace tgon
{


class TgonModelJoyForm :
	public TWindow
{
public:
	TgonModelJoyForm( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))//,
		//m_graphics( new TGraphics( *this ) )
	{
	}

	~TgonModelJoyForm( )
	{
	}

	virtual void OnIdle( ) override
	{
		//m_graphics->BeginScene( );
		//m_graphics->EndScene();


	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{


		V( D3DERR_INVALIDCALL );
	}
	
private:
	TGraphics* m_graphics;
};


}