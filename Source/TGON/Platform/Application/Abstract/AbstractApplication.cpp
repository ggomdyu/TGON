#include "PrecompiledHeader.h"
#include "AbstractApplication.h"


int32_t tgon::AbstractApplication::Run(
	const SpTWindow& window )
{
	bool isQuit = false;
	while ( !isQuit )
	{
		SDL_Event sdlEvent;
		while ( SDL_PollEvent( &sdlEvent ))
		{
			if ( sdlEvent.type == SDL_QUIT )
			{
				isQuit = true;
			}
			else
			{
				if ( window->GetWindowStyle( ).EventHandleable )
				{
					SubMessageProc( window, sdlEvent );
				}
			}
		}
		
		// All of events are processed; Now's the idle time.
		window->OnIdle( );
	}

	return 0;
}

void tgon::AbstractApplication::SubMessageProc(
	const SpTWindow& window,
	const SDL_Event& sdlEvent )
{
	switch ( sdlEvent.type )
	{
	case SDL_WINDOWEVENT:
		switch ( sdlEvent.window.event )
		{
		case SDL_WINDOWEVENT_SHOWN:
			window->OnShow( );
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			window->OnHide( );
			break;
		case SDL_WINDOWEVENT_CLOSE:
//			if ( TWindow::GetCreationCount( ) <= 0 )
			{
				SDL_Quit( );
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			window->OnGetFocus( );
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			window->OnLostFocus( );
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			window->OnSize( sdlEvent.window.data1, sdlEvent.window.data2 );
			break;
		case SDL_WINDOWEVENT_MOVED:
			window->OnMove( sdlEvent.window.data1, sdlEvent.window.data2 );
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			window->OnMaximized( );
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			window->OnMinimized( );
			break;
		case SDL_WINDOWEVENT_LEAVE:
			window->OnMouseLeave( );
			break;
		case SDL_WINDOWEVENT_ENTER:
			window->OnMouseEnter( );
			break;
		}
		break;

	case SDL_MOUSEMOTION:
		window->OnMouseMove( sdlEvent.button.x, sdlEvent.button.y );
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch ( sdlEvent.button.button )
		{
		case SDL_BUTTON_LEFT:
			window->OnLMouseDown( sdlEvent.button.x, sdlEvent.button.y );
			break;
		case SDL_BUTTON_RIGHT:
			window->OnRMouseDown( sdlEvent.button.x, sdlEvent.button.y );
			break;
		case SDL_BUTTON_MIDDLE:
			window->OnMMouseDown( sdlEvent.button.x, sdlEvent.button.y );
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch ( sdlEvent.button.button )
		{
		case SDL_BUTTON_LEFT:
			window->OnLMouseUp( sdlEvent.button.x, sdlEvent.button.y );
			break;
		case SDL_BUTTON_RIGHT:
			window->OnRMouseUp( sdlEvent.button.x, sdlEvent.button.y );
			break;
		case SDL_BUTTON_MIDDLE:
			window->OnMMouseUp( sdlEvent.button.x, sdlEvent.button.y );
			break;
		}
		break;
	}
}