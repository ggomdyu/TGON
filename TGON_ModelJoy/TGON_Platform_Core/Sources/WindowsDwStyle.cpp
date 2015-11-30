#include "stdafx.h"
#include "WindowsDwStyle.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <Windows.h>
	#include <cassert>
	#include "WindowStyle.h"
#endif

void ConvertWsToDw( _In_ const WindowStyle& ws, _Out_ CDwExStyle* const pDwExStyle, _Out_ CDwStyle* const pDwStyle )
{
	/* Extended style */
	if ( ws.TopMost )
	{
		*pDwExStyle |= WS_EX_TOPMOST;
	}

	/* Normal style */
	if ( ws.Maximized )
	{
		*pDwStyle |= WS_MAXIMIZE;
		assert( !ws.Minimized );
	}
	else if ( ws.Minimized )
	{
		*pDwStyle |= WS_MINIMIZE;
	}
	if ( ws.Visible )
	{
		*pDwStyle |= WS_VISIBLE;
	}
	if ( ws.Resizeable )
	{
		*pDwStyle |= WS_THICKFRAME;
	}
	if ( ws.Popup )
	{
		*pDwStyle |= WS_POPUP;
	}
}