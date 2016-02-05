#include "stdafx.h"
#include "WindowsWindow.h"

#include <dwmapi.h>
#include "WindowsWindowUtil.h"


tgon::Window::WindowsWindow::WindowsWindow( bool isEventable, const WindowStyle& wndStyle ) :
	IWindow( isEventable )
{
	// 1. register window information to make
	if ( !RegisterWindow( wndStyle, CallbackMsgProc ))
	{
		MessageBox( GetFocus( ), L"Failed to invoke tgon::RegisterWindow.", L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}

	this->CreateWindowForm( wndStyle );
}


tgon::Window::WindowsWindow::~WindowsWindow( )
{
}


void tgon::Window::WindowsWindow::CreateWindowForm( const WindowStyle& wndStyle )
{
	// 2. set coordinates of window
	int x = wndStyle.x, y = wndStyle.y;
	if ( wndStyle.ShowMiddle )
	{
		x = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5
							  - wndStyle.width*0.5 );
		y = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5
							  - wndStyle.height*0.5 );
	}


	// 3. Make
	DWORD normalWndStyle, exWndStyle;
	ConvertWndStyleToDword( wndStyle, &exWndStyle, &normalWndStyle );

	m_wndHandle = CreateWindowExW( exWndStyle, wndStyle.caption.c_str( ), wndStyle.caption.c_str( ), normalWndStyle, x, y, wndStyle.width, wndStyle.height,
									nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_wndHandle )
	{
		MessageBox( GetFocus( ), L"Failed to invoke CreateWindowEx.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


void tgon::Window::WindowsWindow::BringToTop( )
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


void tgon::Window::WindowsWindow::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}


void tgon::Window::WindowsWindow::SetPosition( const int x, const int y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

void tgon::Window::WindowsWindow::GetPosition( int* x, int* y )
{
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void tgon::Window::WindowsWindow::Move( const int x, const int y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	SetWindowPos( m_wndHandle, nullptr, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}


void tgon::Window::WindowsWindow::Exit( )
{
	PostQuitMessage( 0 );
}


LRESULT tgon::Window::WindowsWindow::CallbackMsgProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	/*
		WARNING! : This logic can arises serious performance issue
	*/


	/*
		CallbackMsgProc can't access member of WindowsWindow.
		So WindowsWindow class uses <Extra memory> that provided when window created.
	*/
	if ( msg == WM_NCCREATE )
	{
		// When invoked 'CreateWindowEx', It throws LPCREATESTRUCT to message callback procedure.
		SetWindowLongPtr( wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(
										LPCREATESTRUCT( lParam )->lpCreateParams )); 
	}


	// Get extra memory pointer
	WindowsWindow* extraMemAsWindow = reinterpret_cast<WindowsWindow*>(
			GetWindowLongPtr( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
		return extraMemAsWindow->CustomMsgProc( wndHandle, msg, wParam, lParam );
	else
		return DefWindowProc( wndHandle, msg, wParam, lParam );
}


LRESULT CALLBACK tgon::Window::WindowsWindow::CustomMsgProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	this->IWindow::SetEvent( msg );

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