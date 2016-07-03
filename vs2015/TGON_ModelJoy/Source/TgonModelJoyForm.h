#pragma once

#include <Window/TWindow.h>
#include <Window/WindowStyle.h>
#include <Console/TConsole.h>

#include <Graphics/Direct3D9/D3D9Error.h>

namespace tgon
{


class TgonModelJoyForm :
	public TWindow
{
public:
	TgonModelJoyForm( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
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
		HRESULT result;
		V( D3DERR_INVALIDCALL );
	}
};


}