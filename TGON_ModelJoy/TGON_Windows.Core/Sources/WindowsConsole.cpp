#include "stdafx.h"
#include "WindowsConsole.h"


#if defined( DEBUG ) | defined( _DEBUG )
#include <Windows.h>

struct WindowsConsoleProxy
{
	static WindowsConsoleProxy& GetInstance( )
	{
		static WindowsConsoleProxy wcp;
		return wcp;
	}

	HANDLE GetOutputHandle( ) const		{ return m_outputHandle; }

private:
	WindowsConsoleProxy( )
	{
		AllocConsole( );

		// Get console handle: the follow function should be invoked after allocated console
		m_outputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
	}

	~WindowsConsoleProxy( )
	{
		CloseHandle( m_outputHandle );
	}

private:
	HANDLE	m_outputHandle;
};

std::wstring tgon::WindowsConsole::m_buf;


void tgon::WindowsConsole::Write( )
{
	WriteConsole( WindowsConsoleProxy::GetInstance( ).GetOutputHandle( ),
				  m_buf.c_str( ), m_buf.length( ), NULL, NULL );

	m_buf.clear( );
}


void tgon::WindowsConsole::WriteLine( )
{
	m_buf += L"\n";

	WindowsConsole::Write( );
}


#endif