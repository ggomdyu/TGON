#include "stdafx.h"
#include "WindowsWindowUtil.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <Windows.h>
	#include <cassert>
	#include "WindowStyle.h"
#endif

void ConvertWsToDw( _In_ const WindowStyle& wndStyle, _Out_ DWORD* const exWndStyle, _Out_ DWORD* const normalWndStyle )
{
	/* Extended style */
	if ( wndStyle.TopMost )
	{
		*exWndStyle |= WS_EX_TOPMOST;
	}

	/* Normal style */
	if ( wndStyle.Maximized )
	{
		*normalWndStyle |= WS_MAXIMIZE;
		assert( !wndStyle.Minimized );
	}
	else if ( wndStyle.Minimized )
	{
		*normalWndStyle |= WS_MINIMIZE;
	}
	if ( wndStyle.Visible )
	{
		*normalWndStyle |= WS_VISIBLE;
	}
	if ( wndStyle.Resizeable )
	{
		*normalWndStyle |= WS_THICKFRAME;
	}
	if ( wndStyle.Popup )
	{
		*normalWndStyle |= WS_POPUP;
	}
}

bool RegisterWindow( const WindowStyle& wndStyle, const WNDPROC wndProc )
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof( wcex );
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wcex.hInstance = GetModuleHandle( nullptr );
	wcex.lpfnWndProc = wndProc;
	wcex.lpszClassName = wndStyle.caption;
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	return RegisterClassEx( &wcex ) != 0;
}