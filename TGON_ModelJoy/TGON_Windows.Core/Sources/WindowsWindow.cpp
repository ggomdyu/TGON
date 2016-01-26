#include "stdafx.h"
#include "WindowsWindow.h"

#include <dwmapi.h>
#include "WindowsWindowUtil.h"


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	IWindow( wndStyle )
{
	// 1. register window information to make
	if ( !RegisterWindow( wndStyle, CallbackMsgProc ))
	{
		MessageBox( GetFocus( ), L"Failed to Invoke tgon::RegisterWindow.", L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}

	this->CreateWindowForm( wndStyle );
}


tgon::WindowsWindow::~WindowsWindow( )
{
}


void tgon::WindowsWindow::CreateWindowForm( const WindowStyle& ws )
{
	// 2. set coordinate of window
	int x = ws.x, y = ws.y;
	if ( ws.ShowMiddle )
	{
		x = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5
							  - ws.width*0.5 );
		y = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5
							  - ws.height*0.5 );
	}


	// 3. Make
	DWORD normalWndStyle, exWndStyle;
	ConvertWndStyleToDword( ws, &exWndStyle, &normalWndStyle );

	m_wndHandle = CreateWindowExW( exWndStyle, ws.caption, ws.caption, normalWndStyle, x, y, ws.width, ws.height,
									nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_wndHandle )
	{
		MessageBox( GetFocus( ), L"Failed to Invoke CreateWindowExW.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


void tgon::WindowsWindow::BringToTop( )
{
	// Is my window foreground?
	const HWND fgWndHandle( GetForegroundWindow( ));
	
	if ( fgWndHandle == m_wndHandle )
		return;


	// Otherwise, bring Process ID
	const DWORD myWndPID = GetWindowThreadProcessId( m_wndHandle, NULL );
	const DWORD fgWndPID = GetWindowThreadProcessId( fgWndHandle, NULL );


	// Attach input
	if ( AttachThreadInput( myWndPID, fgWndPID, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );
		AttachThreadInput( myWndPID, fgWndPID, TRUE );
	}
}


void tgon::WindowsWindow::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}


void tgon::WindowsWindow::SetPosition( int x, int y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}


void tgon::WindowsWindow::Move( int x, int y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	SetWindowPos( m_wndHandle, nullptr, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}


void tgon::WindowsWindow::Exit( )
{
	PostQuitMessage( 0 );
}


LRESULT tgon::WindowsWindow::CallbackMsgProc( HWND wndHandle, unsigned int msg, WPARAM wParam, LPARAM lParam )
{
	if ( msg == WM_DESTROY )
	{
		PostQuitMessage( 0 );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}


void tgon::WindowsWindow::FrameMove( )
{
	BOOL isExistMsg = PeekMessage( &m_msg, NULL, 0, 0, PM_REMOVE );

	if ( isExistMsg )
	{
		TranslateMessage( &m_msg );
		DispatchMessage( &m_msg );
	}
	else
	{
		m_msg.message = WindowEvent::None;
	}
}