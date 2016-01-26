#include "stdafx.h"
#include "WindowsConsole.h"

#include <Windows.h>

#if defined( DEBUG ) | defined( _DEBUG )

	std::wstring		tgon::WindowsConsole::g_buf;

	void tgon::WindowsConsole::WriteLog( )
	{
		static const HANDLE	outputHandle( GetStdHandle( STD_OUTPUT_HANDLE ));

		WriteConsole( outputHandle, g_buf.c_str( ), g_buf.length( ), NULL, NULL );
		g_buf.clear( );
	}

#endif