#include "PrecompiledHeader.h"
#include "TWindowUtil.h"


#include "WindowStyle.h"


uint32_t tgon::Convert_WndStyle_To_SDLFlag(
	const WindowStyle& wndStyle )
{
	uint32_t sdlWindowFlag = 0;

	if ( wndStyle.Resizeable )
	{
		sdlWindowFlag |= SDL_WINDOW_RESIZABLE;
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

	return sdlWindowFlag;
}
