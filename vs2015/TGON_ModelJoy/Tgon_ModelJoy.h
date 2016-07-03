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

#include <SDL_syswm.h>
#include <tgLib/auto_cast.h>
#include <tgLib/array_size.h>


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

	virtual void foo( ) &&
	{

	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
	}

private:
};


}