#pragma once

#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Core/Math/TMath.h>
#include <Window/TWindow.h>
#include <Window/WindowStyle.h>
#include <Application/TApplication.h>
#include <MessageBox/TMessageBox.h>
#include <Graphics/TGraphics.h>
#include <System/WindowSystem.h>

#include <SDL.h>

namespace tgon
{


class Tgon_ModelJoy :
	public TWindow
{
public:
	Tgon_ModelJoy( ) :
		TWindow( WindowStyle::LoadFromXML( L"WindowStyle.xml" ))
	{
		TLog( "OnCreate\n" );
	}

	~Tgon_ModelJoy( )
	{
		TLog( "OnDestroy\n" );
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnMove( int x, int y ) override
	{
		TLog( "OnMove\n" );
	}

	virtual void OnLMouseDown( int x, int y ) override
	{
		TLog( "OnLMouseDown\n" );
	}

private:
};


}