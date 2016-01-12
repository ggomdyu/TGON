#include "stdafx.h"
#include "WindowsWindow.h"

#include <dwmapi.h>
#include "WindowsWindowUtil.h"


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	IWindowImplBase( wndStyle )
{
	// 1. register window information to make
	if ( !RegisterWindow( wndStyle, CallbackMsgProc ))
	{
		MessageBox( GetFocus( ), L"Failed to call RegisterWindow function.", L"WARNING!",
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

	m_wndHandle = CreateWindowEx( exWndStyle, ws.caption, ws.caption, normalWndStyle, x, y, ws.width, ws.height,
									nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_wndHandle )
	{
		MessageBox( GetFocus( ), L"Failed to call CreateWindowEx function.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


void tgon::WindowsWindow::BringToTop( )
{
	// Is current window same with foreground window?
	const HWND fgWndHandle( GetForegroundWindow( ));
	if ( fgWndHandle == m_wndHandle )
		return;


	// 1. otherwise, bring PID from them
	const DWORD curWndPid = GetWindowThreadProcessId( m_wndHandle, NULL );
	const DWORD fgWndPId = GetWindowThreadProcessId( fgWndHandle, NULL );


	// 2. attach input
	if ( AttachThreadInput( curWndPid, fgWndPId, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );
		AttachThreadInput( curWndPid, fgWndPId, TRUE );
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
	/*
		CallbackMsgProc can't access member of WindowsWindow.
		So WindowsWindow class uses <Extra memory> that provided when window created.
	*/
	if ( msg == WM_NCCREATE )
	{
		// When window created by CreateWindow Func, It throws LPCREATESTRUCT to msg Callback.
		// Check 44 lines' func and the last argument
		SetWindowLongPtr( wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(
										LPCREATESTRUCT( lParam )->lpCreateParams )); 
	}


	// Get extra memory ptr through GetWindowLong( .. GWLP_USERDATA )
	WindowsWindow* extraMemAsWindow = reinterpret_cast<WindowsWindow*>(
			GetWindowLongPtr( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
		return extraMemAsWindow->CustomMsgProc( wndHandle, msg, wParam, lParam );
	else
		return DefWindowProc( wndHandle, msg, wParam, lParam );
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


LRESULT CALLBACK tgon::WindowsWindow::CustomMsgProc( HWND wndHandle, unsigned int msg, WPARAM wParam, LPARAM lParam )
{
	IWindowImplBase::CallEventProc( msg );

	if ( msg == WM_DESTROY )
	{
		PostQuitMessage( 0 );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}

	return 0;
}