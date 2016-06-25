#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "../Platform/Slate/PlatformApplication.h"
#include "../Platform/Slate/PlatformProperty.h"
#include "../../Window/Windows/WindowsWindowUtil.h"
#include "../../Window/TWindow.h"

#include <Windows.h>
#include <SDL_syswm.h>


#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


tgon::WindowsWindow::WindowsWindow( 
	const WindowStyle& wndStyle ) :

	AbstractWindow( wndStyle ),
	m_wndHandle( nullptr ),
	m_dcHandle( nullptr )
{
	SDL_SysWMinfo sysWMInfo {0};
	SDL_VERSION( &sysWMInfo.version );
	SDL_GetWindowWMInfo( this->GetSDLWindow( ), &sysWMInfo );

	m_wndHandle = sysWMInfo.info.win.window;
	m_dcHandle = sysWMInfo.info.win.hdc;

	// Initialization After window created ( Which needs a created window )
	this->AdditionalInit( wndStyle );
}

tgon::WindowsWindow::~WindowsWindow( )
{
}

void tgon::WindowsWindow::AdditionalInit( 
	const WindowStyle& wndStyle )
{
	if ( wndStyle.SupportWindowTransparency )
	{
		SetLayeredWindowAttributes( m_wndHandle, NULL, 10,
			LWA_ALPHA );
	}

//#ifdef TGON_SUPPORT_DWMAPI
//	if ( wndStyle.SupportPerPixelTransparency )
//	{
//		BOOL isCompoEnabled = FALSE;
//		DwmIsCompositionEnabled( &isCompoEnabled );
//
//		if ( isCompoEnabled == TRUE )
//		{
//			MARGINS margins{ -1, -1, -1, -1 };
//			DwmExtendFrameIntoClientArea( m_wndHandle, &margins );
//		}
//	}
//#endif
}