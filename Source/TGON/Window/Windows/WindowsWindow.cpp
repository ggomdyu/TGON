#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "../../Platform/PlatformProperty.h"
#include "../../Window/WindowStyle.h"
#include "../../Window/WindowEvent.h"
#include "../../Window/Windows/WindowsWindowUtil.h"
#include "../../Window/TWindow.h"
#include "../../Application/TApplication.h"
#include "../../Console/TConsole.h"

#include <Windows.h>

#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	m_wndStyle( wndStyle ),
	m_msgCallback( wndStyle.msgCallback ),
	m_isDestroyed( false ),
	m_wndHandle( nullptr )
{
	// LazyInitialization will invoked in TWindow
}

tgon::WindowsWindow::~WindowsWindow( )
{
	DestroyWindow( m_wndHandle );
}

void tgon::WindowsWindow::BringToTop( ) 
{
	/*
		@ WARNING
		Windows 98/Me: The system restricts which processes can set the foreground window.
		DO NOT USE SetFocus or SetForegroundWindow functions for .
	*/

	const HWND fgWndHandle( GetForegroundWindow( ));

	
	const DWORD currProcessId = GetWindowThreadProcessId( m_wndHandle, nullptr );
	const DWORD fgProcessId = GetWindowThreadProcessId( fgWndHandle, nullptr );


	if ( AttachThreadInput( currProcessId, fgProcessId, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );

		AttachThreadInput( currProcessId, fgProcessId, TRUE );
	}
}

void tgon::WindowsWindow::Flash( )
{
	FLASHWINFO fwi {0};
	fwi.cbSize = sizeof( FLASHWINFO );
	fwi.dwFlags = FLASHW_CAPTION;
	fwi.dwTimeout = 0;
	fwi.hwnd = this->GetWindowHandle( );
	fwi.uCount = 1;

	FlashWindowEx( &fwi );
}

void tgon::WindowsWindow::GetPosition(
	_Out_ int32_t* x,
	_Out_ int32_t* y ) const 
{
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void tgon::WindowsWindow::GetSize(
	int32_t* width,
	int32_t* height ) const 
{
	/*
		@ WARNING!
		WindowRect contains caption range
	*/
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	*width = rt.right - rt.left;
	*height = rt.bottom - rt.top;
}

std::wstring tgon::WindowsWindow::GetCaption( ) const 
{
	/*
		@ TODO
		Optimize here ( Every calling time, Dynamic allocation is occuring )
	*/

	const int32_t length =
		GetWindowTextLengthW( m_wndHandle )+1; // +1 is for \0

	std::wstring caption( length, L'\0' );
	GetWindowTextW( m_wndHandle, &caption[0], length );

	return caption;
}


void tgon::WindowsWindow::LazyInitialization( )
{
	this->CreateWindowForm( m_wndStyle );

	// Initialization After window created ( Which needs a Created window )
	this->AdditionalInit( m_wndStyle );
}

void tgon::WindowsWindow::CreateWindowForm( 
	const WindowStyle& wndStyle )
{
	// Set coordinates of window
	int32_t x = wndStyle.x;
	int32_t y = wndStyle.y;

	if ( wndStyle.ShowMiddle )
	{
		x = static_cast<int32_t>(
				GetSystemMetrics( SM_CXSCREEN )*0.5 -
				wndStyle.width*0.5 );
		y = static_cast<int32_t>(
				GetSystemMetrics( SM_CYSCREEN )*0.5 -
				wndStyle.height*0.5 );
	}

	// Convert WindowStyle to platform-dependent style.
	DWORD normalStyle, exStyle;
	Convert_wndstyle_to_dword( wndStyle, &exStyle, &normalStyle );



	// Register Window class to Global table.
	std::wstring newClassName;
	bool isSucceed = this->RegisterMyClass( m_wndStyle, &newClassName );

	if ( !isSucceed )
	{
		MessageBoxW(
			this->GetWindowHandle( ),
			L"Failed to invoke tgon::RegisterWindow.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION );

		abort( );
	}


	// Create a Window.
	m_wndHandle = CreateWindowExW(
		exStyle,
		newClassName.c_str(),
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
	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA, // Save window ptr to window-personal storage
		reinterpret_cast<LONG_PTR>( this )
	); 
}

void tgon::WindowsWindow::AdditionalInit(
	const WindowStyle& wndStyle ) 
{
	if ( wndStyle.SupportWindowTransparency )
	{
		SetLayeredWindowAttributes( m_wndHandle, NULL, 255,
			LWA_ALPHA );
	}

#ifdef TGON_SUPPORT_DWMAPI
	if ( wndStyle.SupportPerPixelTransparency )
	{
		BOOL isCompoEnabled = FALSE;
		DwmIsCompositionEnabled( &isCompoEnabled );

		if ( isCompoEnabled == TRUE )
		{
			MARGINS margins{ -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea( m_wndHandle, &margins );
		}
	}
#endif
}

bool tgon::WindowsWindow::RegisterMyClass(
	const WindowStyle& wndStyle,
	std::wstring* outClassName )
{
	const HINSTANCE instanceHandle =
		TApplication::Get( )->GetInstanceHandle( );

	
	//	Each windows must have diffrent class name.
	std::wstring defClassName = L"TGON_Window";
	static int numCreatedWindow = 0;
	defClassName += std::to_wstring( numCreatedWindow );
	*outClassName = defClassName;


	// Fill the Window class information.
	WNDCLASSEX wcex {0};
	wcex.cbSize = sizeof( wcex );
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wcex.hInstance = instanceHandle;
	wcex.lpfnWndProc = ( wndStyle.msgCallback ) ?
		EventableMsgProc : // Custom message proc
		UneventableMsgProc; // Default message proc; more fast than above
	wcex.lpszClassName = defClassName.c_str( );
	wcex.style = CS_DBLCLKS;

	return RegisterClassEx( &wcex ) != 0;
}

LRESULT WINAPI tgon::WindowsWindow::EventableMsgProc(
	HWND wndHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam )
{
	TWindow* extraMemAsWindow = 
		reinterpret_cast<TWindow*>( GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

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
			// m_msgCallback returned 0 or less
			return 0;
		}
	}
	else if ( msg == WM_NCCREATE )
	{
		extraMemAsWindow = reinterpret_cast<TWindow*>(
				LPCREATESTRUCT( lParam )->lpCreateParams );
	
		extraMemAsWindow->m_msgCallback(
			extraMemAsWindow, WindowEvent::Create );
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