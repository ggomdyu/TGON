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
	SDL_SysWMinfo sysWMInfo;
	SDL_GetWindowWMInfo( this->GetSDLWindow( ), &sysWMInfo );

	m_wndHandle = sysWMInfo.info.win.window;
	m_dcHandle = sysWMInfo.info.win.hdc;
}

tgon::WindowsWindow::~WindowsWindow( )
{
}
