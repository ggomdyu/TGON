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
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
	}
};


}