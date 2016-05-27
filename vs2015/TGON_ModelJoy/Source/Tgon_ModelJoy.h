#pragma once

#include <Application/TApplication.h>
#include <Console/TConsole.h>
#include <Core/Math/TMath.h>
#include <Window/WindowEvent.h>
#include <Window/TWindow.h>
#include <Window/WindowStyle.h>
#include <Application/TApplication.h>
#include <MessageBox/TMessageBox.h>
#include <System/WindowSystem.h>


namespace tgon
{


class Tgon_ModelJoy :
	public TApplication
{
public:
	Tgon_ModelJoy( )
	{
		this->SetupWindowComponents( );
	}

	virtual void OnCreate( ) override
	{
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int x, int y ) override
	{
	}

private:
};


}