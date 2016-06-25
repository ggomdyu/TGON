#pragma once

#include <Window/TWindow.h>
#include <Window/WindowStyle.h>


namespace tgon
{


class Tgon_ModelJoy :
	public TWindow
{
public:
	Tgon_ModelJoy( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
	{
	}

	virtual ~Tgon_ModelJoy( )
	{
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
	}
};


}