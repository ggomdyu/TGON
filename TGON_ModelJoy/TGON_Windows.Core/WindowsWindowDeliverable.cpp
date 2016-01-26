#include "stdafx.h"
#include "WindowsWindowDeliverable.h"

#include <dwmapi.h>
#include "WindowsWindowUtil.h"


tgon::WindowsWindowDeliverable::WindowsWindowDeliverable( const WindowStyle& wndStyle ) :
	IWindow( wndStyle )
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


tgon::WindowsWindowDeliverable::~WindowsWindowDeliverable( )
{
}


void tgon::WindowsWindowDeliverable::CreateWindowForm( const WindowStyle& ws )
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


void tgon::WindowsWindowDeliverable::BringToTop( )
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


void tgon::WindowsWindowDeliverable::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}


void tgon::WindowsWindowDeliverable::SetPosition( int x, int y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}


void tgon::WindowsWindowDeliverable::Move( int x, int y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	SetWindowPos( m_wndHandle, nullptr, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}


void tgon::WindowsWindowDeliverable::Exit( )
{
	PostQuitMessage( 0 );
}


LRESULT tgon::WindowsWindowDeliverable::CallbackMsgProc( HWND wndHandle, unsigned int msg, WPARAM wParam, LPARAM lParam )
{
	/*
		CallbackMsgProc can't access member of WindowsWindowDeliverable.
		So WindowsWindowDeliverable class uses <Extra memory> that provided when window created.
	*/
	if ( msg == WM_NCCREATE )
	{
		// When window created by CreateWindow Func, It throws LPCREATESTRUCT to msg Callback.
		// Check 44 lines' func and the last argument
		SetWindowLongPtr( wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(
										LPCREATESTRUCT( lParam )->lpCreateParams )); 
	}


	// Get extra memory ptr through GetWindowLong( .. GWLP_USERDATA )
	WindowsWindowDeliverable* extraMemAsWindow = reinterpret_cast<WindowsWindowDeliverable*>(
			GetWindowLongPtr( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
		return extraMemAsWindow->CustomMsgProc( wndHandle, msg, wParam, lParam );
	else
		return DefWindowProc( wndHandle, msg, wParam, lParam );
}


void tgon::WindowsWindowDeliverable::FrameMove( )
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


LRESULT CALLBACK tgon::WindowsWindowDeliverable::CustomMsgProc( HWND wndHandle, unsigned int msg, WPARAM wParam, LPARAM lParam )
{
	IWindow::CallEventProc( msg );

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