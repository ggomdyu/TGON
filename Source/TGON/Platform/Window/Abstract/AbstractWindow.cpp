#include "PrecompiledHeader.h"
#include "AbstractWindow.h"

#include "../../MessageBox/TMessageBox.h"
#include "../TWindowUtil.h"


tgon::AbstractWindow::AbstractWindow( const WindowStyle& wndStyle ) : 
	m_isWindowHandleable( wndStyle.EventHandleable )
{
	this->SetupWindow( wndStyle );
}

tgon::AbstractWindow::~AbstractWindow( )
{
	this->Close( );
}

void tgon::AbstractWindow::SetupWindow( 
	const WindowStyle& wndStyle )
{
	int32_t x = wndStyle.x;
	int32_t y = wndStyle.y;

	/* 
		Set coordinates of window
	*/
	if ( wndStyle.ShowMiddle )
	{
		// TODO: support multi-window
		//int32_t numVideoDisplay = SDL_GetNumVideoDisplays( );

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode( 0, &displayMode );
		
		x = static_cast<int32_t>( displayMode.w*0.5 - wndStyle.width*0.5 );
		y = static_cast<int32_t>( displayMode.h*0.5 - wndStyle.height*0.5 );
	}

	/*
		Create window
	*/
	m_sdlWindow = SDL_CreateWindow( 
		wndStyle.title.c_str( ),
		x, 
		y, 
		wndStyle.width,
		wndStyle.height,
		Convert_WindowStyle_To_SDLStyle( wndStyle )
	);
}

void tgon::AbstractWindow::SetPosition( 
	int32_t x, 
	int32_t y )
{
	SDL_SetWindowPosition( m_sdlWindow, x, y );
}

void tgon::AbstractWindow::Move(
	int32_t x,
	int32_t y )
{
	int32_t currX, currY;
	this->GetPosition( &currX, &currY );

	SDL_SetWindowPosition( m_sdlWindow, currX+x, currY+y );
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
