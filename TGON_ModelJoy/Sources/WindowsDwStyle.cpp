#include "stdafx.h"
#include "WindowsDwStyle.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include "WindowStyle.h"
#endif

void ConvertWsToDw( _In_ const WindowStyle& ws, _Out_ CDwExStyle* const pDwExStyle, _Out_ CDwStyle* const pDwStyle )
{
	/* Extended style */
	if ( ws.bTopMost )
	{
		*pDwExStyle |= WS_EX_TOPMOST;
	}

	/* Normal style */
	*pDwStyle = WS_OVERLAPPEDWINDOW;

	if ( ws.bMaximized )
	{
		*pDwStyle |= WS_MAXIMIZE;
	}
	else if ( ws.bMinimized )
	{
		*pDwStyle |= WS_MINIMIZE;
	}
	if ( ws.bVisible )
	{
		*pDwStyle |= WS_VISIBLE;
	}
}