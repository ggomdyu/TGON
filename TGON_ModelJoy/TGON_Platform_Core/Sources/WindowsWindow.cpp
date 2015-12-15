#include "stdafx.h"
#include "WindowsWindow.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <Windows.h>
	#include <dwmapi.h>

	#include "WindowStyle.h"
	#include "WindowsWindowUtil.h"
#endif

tgon::WindowsWindow::WindowsWindow( const WindowStyle& ws ) :
	GenericWindow( ws )
{
	// 1. register window information to make
	if ( !RegisterWindow( ws, CallbackMsgProc ))
	{
		MessageBox( GetFocus( ), L"Failed to progress RegisterWindow function.", L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}

	this->MakeWindow( ws );
}


tgon::WindowsWindow::~WindowsWindow( )
{
}


void tgon::WindowsWindow::MakeWindow( const WindowStyle& ws )
{
	// 2. set coordinate of window
	int x = ws.x, y = ws.y;
	if ( ws.ShowMiddle )
	{
		x = static_cast<int>( GetSystemMetrics( SM_CXSCREEN )*0.5 - ws.width*0.5 );
		y = static_cast<int>( GetSystemMetrics( SM_CYSCREEN )*0.5 - ws.height*0.5 );
	}


	// 3. Make
	DWORD normalWindowStyle = 0;
	DWORD exWindowStyle = 0;
	ConvertWsToDw( ws, &exWindowStyle, &normalWindowStyle );

	m_wndHandle = CreateWindowEx( exWindowStyle, ws.caption, ws.caption, normalWindowStyle, x, y, ws.width, ws.height,
									nullptr, nullptr, GetModuleHandle( NULL ), this );
	if ( !m_wndHandle )
	{
		MessageBox( GetFocus( ), L"Failed to progress CreateWindowEx function.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


HWND tgon::WindowsWindow::GetWindowHandle( ) const
{
	return m_wndHandle;
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

LRESULT tgon::WindowsWindow::CallbackMsgProc( HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam )
{
	/*
		CallbackMsgProc is static function so it can't access member of WindowsWindow.
		It's solved by calling CustomMsgProc function.
	*/
	if ( msg == WM_NCCREATE )
	{
		SetWindowLong( wndHandle, GWLP_USERDATA, reinterpret_cast<LONG>((
				LPCREATESTRUCT( lParam )->lpCreateParams ))); 
	}

	WindowsWindow* pWindow = reinterpret_cast<WindowsWindow*>(
			GetWindowLong( wndHandle, GWLP_USERDATA ));

	if ( pWindow )
		return pWindow->CustomMsgProc( wndHandle, msg, wParam, lParam );
	else
		return DefWindowProc( wndHandle, msg, wParam, lParam );
}

bool tgon::WindowsWindow::PumpWindowEvent( )
{
	MSG msg;
	BOOL isExistMsg = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );

	if ( isExistMsg )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return isExistMsg != 0;
}

LRESULT CALLBACK tgon::WindowsWindow::CustomMsgProc( HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_CREATE:
		{
//			MARGINS margins = { -1, -1, -1, -1 };
//			DwmExtendFrameIntoClientArea( wndHandle, &margins );
		}
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
	
	return 0;
}