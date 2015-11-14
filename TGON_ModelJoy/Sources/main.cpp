#include "stdafx.h"

#include "GenericWindow.h"
#include "GenericApplication.h"
#include "ToolManager.h"
#include "FBXModel.h"
#include "WindowMessage.h"
#include "Direct3D.h"

using namespace tgon;

int KapMain( int argc, char* argv[] )
{
	WindowStyle ws;
	ws.bShowMiddle = true;
	ws.nWidth = 1000;
	ws.nHeight = 1000;
	ws.wsCaption = L"ModelJoy";


	const std::shared_ptr<PlatformWindow> pWindow( new PlatformWindow( ws ));
	pWindow->Make( );


	CDirect3D::get( )->Initialize( pWindow->GetWindowHandle( ));


	std::unique_ptr<CFBXModel> pModel( new CFBXModel );
	pModel->LoadMesh( "Resource\\FBXModel\\humanoid.FBX" );


	PlatformApplication::AddWindow( "MainWnd", pWindow );
	while ( pWindow->GetCurrentMessage( ) != WindowMessage::Destroy )
	{
		if ( !PlatformApplication::ResponseMessage( ))
		{
			// Idle time
			CDirect3D::get( )->BeginDraw( );
  			pModel->Render( );
			CDirect3D::get( )->EndDraw( );
		}
	}
	return 0;
}