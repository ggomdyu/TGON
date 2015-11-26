#include "stdafx.h"

#include "GenericWindow.h"
#include "GenericApplication.h"
#include "FBXModel.h"
#include "WindowMessage.h"
#include "WindowStyle.h"
#include "Direct3D9.h"

using namespace tgon;

int KapMain( int argc, char* argv[] )
{
	WindowStyle ws;
	ws.bShowMiddle = true;
	ws.nWidth = 1200;
	ws.nHeight = 1000;
	ws.bPopUp = true;
	ws.wsCaption = L"ModelJoy";

	const std::shared_ptr<Window> pWindow( new Window( ws ));
	pWindow->Make( );

	//CDirect3D9::CDirect3D9( );
	CDirect3D9::get()->Initialize(pWindow->GetWindowHandle());
	Application::AddWindow( "MainWnd", pWindow );

	// test
	std::unique_ptr<CFBXModel> pModel( new CFBXModel( "Resources\\FBXModel\\humanoid.FBX" ));


	while ( pWindow->GetWindowEvent( ) != WindowEvent::Destroy )
	{
		if ( !Application::ResponseMessage( ))
		{
			CDirect3D9::get( )->BeginDraw( );
			pModel->Render();
			CDirect3D9::get( )->EndDraw( );
		}
		else
		{
			if ( pWindow->GetWindowEvent() == WM_RBUTTONDOWN )
			{
				break;
			}
		}
	}
	return 0;
}