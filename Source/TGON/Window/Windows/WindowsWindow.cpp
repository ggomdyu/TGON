#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "../../Config/Platform/PlatformProperty.h"
#include "../../Window/WindowStyle.h"
#include "../../Window/WindowEvent.h"
#include "../../Window/Windows/WindowsWindowUtil.h"
#include "../../Window/TWindow.h"
#include "../../Console/TConsole.h"
#include "../../String/TString.h"


#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif

const wchar_t tgon::WindowsWindow::WndClassName[] = L"TGON_Window";


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	m_msgCallback( wndStyle.msgCallback ),
	m_isDestroyed( false ),
	m_wndHandle( nullptr )
{
	// Register window class to global table.
	bool isSucceed = ( wndStyle.msgCallback ) ?
				RegisterClass( wndStyle, EventableMsgProc ) :
				RegisterClass( wndStyle, UneventableMsgProc );

	if ( !isSucceed &&
		 GetLastError() != ERROR_CLASS_ALREADY_EXISTS )
	{
		MessageBoxW( this->GetWindowHandle(), L"Failed to invoke tgon::RegisterWindow.", L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION );
		abort();
	}

	
	this->CreateWindowForm( wndStyle ); // CreateWindowEx will be invoked.
	this->AdditionalInit( wndStyle );
}

tgon::WindowsWindow::~WindowsWindow( )
{
	DestroyWindow( m_wndHandle );
}

void tgon::WindowsWindow::BringToTop( ) 
{
	const HWND fg_wndHandle( GetForegroundWindow( ));

	// Is my window foreground?
	if ( fg_wndHandle == m_wndHandle )
		return;

	// Otherwise, bring Process ID
	const DWORD my_wndProcessID = GetWindowThreadProcessId(
		m_wndHandle, NULL );
	const DWORD fg_wndProcessID = GetWindowThreadProcessId(
		fg_wndHandle, NULL );

	// Attach input
	if ( AttachThreadInput( my_wndProcessID, fg_wndProcessID, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );

		AttachThreadInput( my_wndProcessID, fg_wndProcessID, TRUE );
	}
}

void tgon::WindowsWindow::FlashWindow( )
{
	FLASHWINFO fwi {0};
	fwi.cbSize = sizeof( FLASHWINFO );
	fwi.dwFlags = FLASHW_CAPTION;
	fwi.dwTimeout = 0;
	fwi.hwnd = this->GetWindowHandle( );
	fwi.uCount = 1;

	FlashWindowEx( &fwi );
}

void tgon::WindowsWindow::GetPosition( int32_t* const x,
									   int32_t* const y ) const 
{
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void tgon::WindowsWindow::GetSize( int32_t* const width,
								   int32_t* const height ) const 
{
	/*
		This RECT contains caption range
	*/
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	*width = rt.right - rt.left;
	*height = rt.bottom - rt.top;
}

std::wstring tgon::WindowsWindow::GetCaption( ) const 
{
	const uint32_t length =
		GetWindowTextLengthW( m_wndHandle )+1; // +1 is for \0

	std::wstring caption( length, L'\0' );

	GetWindowTextW( m_wndHandle, &caption[0], length );
	return caption;
}

void tgon::WindowsWindow::CreateWindowForm( const WindowStyle& wndStyle ) 
{
	// set coordinates of window
	uint32_t x = wndStyle.x;
	uint32_t y = wndStyle.y;

	if ( wndStyle.ShowMiddle )
	{
		x = static_cast<uint32_t>( GetSystemMetrics( SM_CXSCREEN )*0.5 -
								   wndStyle.width*0.5 );
		y = static_cast<uint32_t>( GetSystemMetrics( SM_CYSCREEN )*0.5 -
								   wndStyle.height*0.5 );
	}


	// Convert WindowStyle to platform-dependent style.
	DWORD normalStyle, exStyle;
	convert_wndstyle_to_dword( wndStyle, &exStyle, &normalStyle );


	// Window creation
	m_wndHandle = CreateWindowExW(
			exStyle,
			WindowsWindow::WndClassName,
			wndStyle.caption.c_str(),
			normalStyle,
			x, y, wndStyle.width, wndStyle.height,
			nullptr,
			nullptr,
			GetModuleHandle( NULL ),
			this
		);


	if ( !m_wndHandle )
	{
		MessageBoxW( GetFocus( ),
					 L"Failed to invoke CreateWindowEx.",
					 L"WARNING!",
					 MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}


	/*
		- Why use SetWindowLongPtrW?

		CallbackMsgProc can't access member of WindowsWindow.
		So WindowsWindow class uses <Extra memory>, which have provided when window had created.
	*/
	SetWindowLongPtrW( m_wndHandle, GWLP_USERDATA,
					   reinterpret_cast<LONG_PTR>( this )); 
}

void tgon::WindowsWindow::AdditionalInit( const WindowStyle& wndStyle ) 
{
	if ( wndStyle.SupportWindowTransparency )
	{
		SetLayeredWindowAttributes( m_wndHandle, NULL, 255, LWA_ALPHA );
	}

	if ( wndStyle.SupportPerPixelTransparency )
	{
		BOOL isCompEnabled = FALSE;
		DwmIsCompositionEnabled( &isCompEnabled );

		if ( isCompEnabled == TRUE )
		{
			MARGINS margins{ -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea( m_wndHandle, &margins );
		}
	}
}

LRESULT WINAPI tgon::WindowsWindow::EventableMsgProc(
		HWND wndHandle,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam )
{
	/*
		TODO: DANGEROUS CODE - Repair this casting

		@ Here are two ways to solve problem:
		1. Delay start of message pumping
		2. Lazy initialization of window; User must call init function
		   when created 'TWindow'.
	*/
	TWindow* extraMemAsWindow = reinterpret_cast<TWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
	{
		if ( extraMemAsWindow->m_msgCallback( extraMemAsWindow,
				static_cast<WindowEvent>( msg )) > 0 )
		{
			if ( msg == WM_DESTROY )
			{
				PostQuitMessage( 0 );
				extraMemAsWindow->m_isDestroyed = true;
			}
		}
		else
		{
			// Callback function returned zero
			return 0;
		}
	}
	else if ( msg == WM_NCCREATE )
	{
		extraMemAsWindow = reinterpret_cast<TWindow*>(
				LPCREATESTRUCT( lParam )->lpCreateParams );
	
		extraMemAsWindow->m_msgCallback(
				extraMemAsWindow,
				WindowEvent::Create
			);
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}

LRESULT WINAPI tgon::WindowsWindow::UneventableMsgProc(
		HWND wndHandle,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam )
{
	if ( msg == WM_DESTROY )
	{
		TWindow* extraMemAsWindow = reinterpret_cast<TWindow*>(
			GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));
		
		extraMemAsWindow->m_isDestroyed = true;
		PostQuitMessage( 0 );

		return 0;
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}