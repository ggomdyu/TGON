#include "stdafx.h"
#include "WindowsWindow.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <dwmapi.h>
	#include "msgstream.h"
	#include "WindowStyle.h"
	#include "WindowsDwStyle.h"
#endif

NSBEGIN( tgon );
WindowsWindow::WindowsWindow( const WindowStyle& ws ) :
	GenericWindow( ws )
{
	// 1. Register window info
	if ( !RegisterWindow( ws ))
	{
		msg::out << "Failed to call RegisterWindow function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
}

WindowsWindow::~WindowsWindow( )
{
}

void WindowsWindow::Make( )
{
	const WindowStyle& ws( this->GetWindowStyle( ));

	CDwExStyle dwExStyle;
	CDwStyle dwStyle;
	ConvertWsToDw( ws, &dwExStyle, &dwStyle );

	// 2. Set window's coordinate
	int x = ws.X, y = ws.Y;
	if ( ws.ShowMiddle )
	{
		x = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5 - ws.Width*0.5 );
		y = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5 - ws.Height*0.5 );
	}

	// 3. Make
	m_window_handle = CreateWindowEx( dwExStyle, ws.Caption, ws.Caption, dwStyle, x, y, ws.Width, ws.Height,
						nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_window_handle )
	{
		msg::out << "Failed to call CreateWindowEx function." << " ( errCode : " << GetLastError( ) << " )" << msg::warn;
		//goto retry_make_window;
	}
}

HWND WindowsWindow::GetWindowHandle( ) const
{
	return m_window_handle;
}

void WindowsWindow::BringToTop( )
{
	// Foreground window currently?
	const HWND foreground_handle( GetForegroundWindow( ));
	if ( foreground_handle == m_window_handle )
		return;

	// 1. Otherwise, get each other window's PID 
	const DWORD current_window_pid = GetWindowThreadProcessId( m_window_handle, NULL );
	const DWORD foreground_window_pid = GetWindowThreadProcessId( foreground_handle, NULL );

	// 2. Request to system to attach input what I bring to top
	if ( AttachThreadInput( current_window_pid, foreground_window_pid, TRUE ))
	{
		SetForegroundWindow( m_window_handle );
		BringWindowToTop( m_window_handle );
		AttachThreadInput( current_window_pid, foreground_window_pid, TRUE );
	}
}

void WindowsWindow::Show( )
{
	ShowWindow( m_window_handle, SW_NORMAL );
}

void WindowsWindow::SetPosition( const int x, const int y )
{
	SetWindowPos( m_window_handle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

void WindowsWindow::Move( const int x, const int y )
{
	RECT rt;
	GetWindowRect( m_window_handle, &rt );

	SetWindowPos( m_window_handle, nullptr, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}

bool WindowsWindow::RegisterWindow( const WindowStyle& ws, const HICON hIcon, const HCURSOR hCursor )
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof( wcex );
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = hCursor;
	wcex.hIcon = hIcon;
	wcex.hInstance = GetModuleHandle( nullptr );
	wcex.lpfnWndProc = MsgBaseProc;
	wcex.lpszClassName = ws.Caption;
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	return RegisterClassEx( &wcex ) != 0;
}

LRESULT WindowsWindow::MsgBaseProc( HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg == WM_NCCREATE )
	{
		/*
			When window created, receive allocated pointer( WindowsWindow* ) by 'CreateWindowEx' funtion's last parameter.
			because MsgBaseProc func is static, so it can't access WindowsWindow's stack data.

			¡Ø So this func works to make possible to access stack data through call MsgDelivedProc.
		*/
		SetWindowLong( hWnd, GWL_USERDATA, reinterpret_cast<LONG>((
				LPCREATESTRUCT( lParam )->lpCreateParams ))); 
	}

	WindowsWindow* pWindow = reinterpret_cast<WindowsWindow*>(
			GetWindowLong( hWnd, GWL_USERDATA ));

	if ( pWindow )
		return pWindow->MsgDelivedProc( hWnd, uMsg, wParam, lParam );
	else
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK WindowsWindow::MsgDelivedProc( HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam )
{
	SetWindowEvent( uMsg );

	/* WARN: DON'T ADD CASE into the follow switch-syntax!!!! */
	switch( uMsg )
	{
	case WM_CREATE:
		{
			MARGINS margins = { -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea( hWnd, &margins );
		}
		break;

	case WM_CLOSE:
//		msg::out << "Close clicking by right mouse button" << msg::warn;
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	
	return 0;
}
NSEND( );