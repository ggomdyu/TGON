#include "stdafx.h"
#include "WindowsWindow.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
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
		msg::out << "Failed to call RegisterWindow function." << msg::warn;
		abort( );
	}
}

WindowsWindow::~WindowsWindow( )
{
}

void WindowsWindow::Make( )
{
	CDwExStyle dwExStyle;
	const WindowStyle& ws = this->GetWindowStyle( );

	CDwStyle dwStyle;
	ConvertWsToDw( ws, &dwExStyle, &dwStyle );

	// 2. Set window's coordinate
	int nX = ws.nX, nY = ws.nY;
	if ( ws.bShowMiddle )
	{
		nX = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5 - ws.nWidth*0.5 );
		nY = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5 - ws.nHeight*0.5 );
	}

	// 3. Make
	m_hWnd = CreateWindowEx( dwExStyle, ws.wsCaption, ws.wsCaption, dwStyle,
								nX, nY, ws.nWidth, ws.nHeight,
						nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_hWnd )
	{
		msg::out << "Failed to call CreateWindowEx function." << msg::warn;
		//goto retry_make_window;
	}
}

HWND WindowsWindow::GetWindowHandle( ) const
{
	return m_hWnd;
}

void WindowsWindow::BringToTop( )
{
	//HWND hForeground;
	//DWORD dwId, foreground_id;
	//hForeground = GetForegroundWindow( );

	//if ( hForeground == m_hWnd )
	//	return;

	//foreground_id = GetWindowThreadProcessId( hForeground, NULL );
	//id = GetWindowThreadProcessId( m_hWnd, NULL );

	//if ( AttachThreadInput( id, foreground_id, TRUE ))
	//{
	//	SetForegroundWindow( m_hWnd );
	//	BringWindowToTop( m_hWnd );
	//	AttachThreadInput( id, foreground_id, TRUE );
	//}
}

void WindowsWindow::Show( )
{
	ShowWindow( m_hWnd, SW_NORMAL );
}

void WindowsWindow::SetPosition( const int x, const int y )
{
	SetWindowPos( m_hWnd, NULL, x, y, 0, 0, SWP_NOSIZE );
}

void WindowsWindow::Move( const int x, const int y )
{
	RECT rt;
	GetWindowRect( m_hWnd, &rt );

	SetWindowPos( m_hWnd, NULL, rt.left+x, rt.top+y, 0, 0, SWP_NOSIZE );
}

bool WindowsWindow::RegisterWindow( const WindowStyle& ws, const HICON hIcon, const HCURSOR hCursor )
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof( wcex );
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = hCursor;
	wcex.hIcon = hIcon;
	wcex.hInstance = GetModuleHandle( NULL );
	wcex.lpfnWndProc = MsgBaseProc;
	wcex.lpszClassName = ws.wsCaption;
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	return RegisterClassEx( &wcex ) != 0;
}

LRESULT WindowsWindow::MsgBaseProc( HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg == WM_NCCREATE )
	{
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
	switch( uMsg )
	{
	case WM_CREATE:
	case WM_MOVE:
	case WM_SIZE:
		SetCurrentMessage( uMsg );
		break;

	case WM_DESTROY:
		SetCurrentMessage( uMsg );
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	
	return 0;
}
NSEND( );