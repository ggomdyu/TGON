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
	Tgon_ModelJoy( /*int argc, char* argv*/ )
	{
		this->SetupWindowComponents( );
	}

	virtual void OnCreate( ) override
	{
		TMessageBox::Show( L"æ»≥Á«œΩ≈∞≈º¿ §ª§ª" );
	}

	virtual void OnIdle( ) override
	{
		TLog( "z" );
	}

private:
};


}