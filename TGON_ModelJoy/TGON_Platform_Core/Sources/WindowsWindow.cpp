#include "stdafx.h"
#include "WindowsWindow.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <Windows.h>
	#include <dwmapi.h>
	#include "msgstream.h"
	#include "WindowStyle.h"
	#include "WindowsWindowUtil.h"
#endif

tgon::WindowsWindow::WindowsWindow( const WindowStyle& ws ) :
	GenericWindow( ws )
{
	// 1. Register window info
	if ( !RegisterWindow( ws, CallbackMsgProc ))
	{
		msg::out << "Failed to call RegisterWindow function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
}

tgon::WindowsWindow::~WindowsWindow( )
{
}

void tgon::WindowsWindow::Make( )
{
	const WindowStyle& ws( this->GetWindowStyle( ));

	DWORD normalWindowStyle = 0, exWindowStyle = 0;
	ConvertWsToDw( ws, &exWindowStyle, &normalWindowStyle );

	// 2. Set window's coordinate
	int x = ws.x, y = ws.y;
	if ( ws.ShowMiddle )
	{
		x = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5 - ws.width*0.5 );
		y = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5 - ws.height*0.5 );
	}

	// 3. Make
	m_wndHandle = CreateWindowEx( exWindowStyle, ws.caption, ws.caption, normalWindowStyle, x, y, ws.width, ws.height,
						nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_wndHandle )
	{
		msg::out << "Failed to call CreateWindowEx function." << " ( errCode : " << GetLastError( ) << " )" << msg::warn;
		//goto retry_make_window;
	}
}

HWND tgon::WindowsWindow::GetWindowHandle( ) const
{
	return m_wndHandle;
}

void tgon::WindowsWindow::BringToTop( )
{
	// Current window is Foreground window?
	const HWND topWndHandle( GetForegroundWindow( ));
	if ( topWndHandle == m_wndHandle )
		return;


	// 1. Otherwise, get each other window's PID 
	const DWORD curWndPid = GetWindowThreadProcessId( m_wndHandle, NULL );
	const DWORD topWndPid = GetWindowThreadProcessId( topWndHandle, NULL );

	// 2. Attach input
	if ( AttachThreadInput( curWndPid, topWndPid, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );
		AttachThreadInput( curWndPid, topWndPid, TRUE );
	}
}

void tgon::WindowsWindow::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}

void tgon::WindowsWindow::SetPosition( const int x, const int y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

void tgon::WindowsWindow::Move( const int x, const int y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	SetWindowPos( m_wndHandle, nullptr, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}

LRESULT tgon::WindowsWindow::CallbackMsgProc( HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam )
{
	/*
		CallbackMsgProc is static function so it can't access WindowsWindow's member.
		This problem is solved by calling CustomMsgProc function.
	*/

	if ( msg == WM_NCCREATE )
	{
		SetWindowLong( wndHandle, GWL_USERDATA, reinterpret_cast<LONG>((
				LPCREATESTRUCT( lParam )->lpCreateParams ))); 
	}

	WindowsWindow* pWindow = reinterpret_cast<WindowsWindow*>(
			GetWindowLong( wndHandle, GWL_USERDATA ));

	if ( pWindow )
		return pWindow->CustomMsgProc( wndHandle, msg, wParam, lParam );
	else
		return DefWindowProc( wndHandle, msg, wParam, lParam );
}

LRESULT CALLBACK tgon::WindowsWindow::CustomMsgProc( HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam )
{
	SetWindowEvent( msg );

	switch( msg )
	{
	case WM_CREATE:
		{
			MARGINS margins = { -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea( wndHandle, &margins );
		}
		break;

	case WM_CLOSE:
		break;

	default:
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
	
	return 0;
}