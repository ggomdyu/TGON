#include "PrecompiledHeader.h"
#include "AbstractWindow.h"

#include "../../MessageBox/TMessageBox.h"
#include "../TWindowUtil.h"


int32_t tgon::AbstractWindow::ms_sdlWindowCount = 0;


tgon::AbstractWindow::AbstractWindow( 
	const WindowStyle& wndStyle ) :

	m_wndStyle( wndStyle )
{
	this->SetupWindow( );
}

tgon::AbstractWindow::~AbstractWindow( )
{
	this->Close( );
}

void tgon::AbstractWindow::SetupWindow( )
{
	// Set coordinates of window
	if ( m_wndStyle.ShowMiddle )
	{
		// TODO: support multi-window

		SDL_DisplayMode displayMode;
		if ( SDL_GetCurrentDisplayMode( 0, &displayMode ) < 0 )
		{
			// TODO: Error Log
		}
		
		m_wndStyle.x = static_cast<int32_t>(
			displayMode.w*0.5 -
			m_wndStyle.width*0.5 );
		m_wndStyle.y = static_cast<int32_t>(
			displayMode.h*0.5 -
			m_wndStyle.height*0.5 );
	}

	const uint32_t sdlWindowFlag = 
		Convert_WndStyle_To_SDLFlag( m_wndStyle );

	m_sdlWindow = SDL_CreateWindow( 
		"¾ÆÂ¯³ª",
		m_wndStyle.x,
		m_wndStyle.y,
		m_wndStyle.width,
		m_wndStyle.height,
		sdlWindowFlag
	);

	++ms_sdlWindowCount;
	SDL_SetWindowData( m_sdlWindow, "WindowPtr", this );
}

void tgon::AbstractWindow::SetPosition( 
	int32_t x, 
	int32_t y )
{
	SDL_SetWindowPosition( m_sdlWindow, x, y );
}

void tgon::AbstractWindow::SetScale( 
	int32_t width, 
	int32_t height )
{
	SDL_SetWindowSize( m_sdlWindow, width, height );
}

void tgon::AbstractWindow::SetCaption( 
	const wchar_t* title )
{
}
