#pragma once
#define WIN32_LEAN_AND_MEAN /* fwd declare */
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

struct WindowStyle;


namespace tgon
{
	void ConvertWndStyleToDword( const WindowStyle&,
						_Out_ DWORD* const exWndStyle,
						_Out_ DWORD* const normalWndStyle );

	bool RegisterWindow( const WindowStyle& wndStyle, const WNDPROC wndProc );
}