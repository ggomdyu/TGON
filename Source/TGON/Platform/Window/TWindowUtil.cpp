#include "PrecompiledHeader.h"
#include "TWindowUtil.h"

#include "WindowStyle.h"


uint32_t tgon::Convert_WindowStyle_To_SDLStyle(
	const WindowStyle& wndStyle )
{
	uint32_t sdlWindowFlag = 0;

	if ( wndStyle.ClipCursor )
	{
		sdlWindowFlag |= SDL_WINDOW_INPUT_GRABBED;
	}
	if ( wndStyle.FullScreen )
	{
		sdlWindowFlag |= SDL_WINDOW_FULLSCREEN;
	}
	if ( wndStyle.Maximized )
	{
		sdlWindowFlag |= SDL_WINDOW_MAXIMIZED;
	}
	if ( wndStyle.Minimized )
	{
		sdlWindowFlag |= SDL_WINDOW_MINIMIZED;
	}
	if ( wndStyle.Resizeable )
	{
		sdlWindowFlag |= SDL_WINDOW_RESIZABLE;
	}
	if ( !wndStyle.ShowImmediately )
	{
		sdlWindowFlag |= SDL_WINDOW_HIDDEN;
	}

	return sdlWindowFlag;
}
