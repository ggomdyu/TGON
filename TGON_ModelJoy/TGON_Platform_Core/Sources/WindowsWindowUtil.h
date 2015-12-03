#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#define WIN32_LEAN_AND_MEAN /* fwd declare */
	#include <Windows.h>
#endif

struct WindowStyle;

void ConvertWsToDw( _In_ const WindowStyle&,
					_Out_ DWORD* const exWndStyle, _Out_ DWORD* const normalWndStyle );
bool RegisterWindow( _In_ const WindowStyle& wndStyle, const WNDPROC wndProc );