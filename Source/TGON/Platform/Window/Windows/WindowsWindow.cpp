#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "../Platform/Slate/PlatformApplication.h"
#include "../Platform/Slate/PlatformProperty.h"
#include "../../Window/WindowStyle.h"
#include "../../Window/Windows/WindowsWindowUtil.h"
#include "../../Window/TWindow.h"
#include "../../../Core/String/TString.h"

#include <Windows.h>

#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	AbstractWindow( wndStyle ),
	m_isDestroyed( false ),
	m_wndHandle( nullptr )
{
	this->CreateWindowForm( this->GetWindowStyle( ), wndStyle.EventHandleable );

	// Initialization After window created ( Which needs a created window )
	this->AdditionalInit( this->GetWindowStyle( ));
}

tgon::WindowsWindow::~WindowsWindow( )
{
	DestroyWindow( m_wndHandle );
}

void tgon::WindowsWindow::BringToTop( ) 
{
	/*
		After Windows 98/Me: The system restricts which processes can set the foreground window.
		So, you can't switch the focus freely by only SetFocus or SetForegroundWindow.
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

void tgon::WindowsWindow::GetPosition( int32_t* x, int32_t* y ) const 
{
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void tgon::WindowsWindow::GetSize( int32_t* width, int32_t* height ) const 
{
	RECT rt;
	// @ WARNING! : WindowRect contains caption range
	GetWindowRect( m_wndHandle, &rt );

	*width = rt.right - rt.left;
	*height = rt.bottom - rt.top;
}

void tgon::WindowsWindow::GetCaption( wchar_t* caption ) const
{
	const int32_t length = GetWindowTextLengthW( m_wndHandle );
	GetWindowTextW( m_wndHandle, caption, length );
}

void tgon::WindowsWindow::CreateWindowForm( const WindowStyle& wndStyle, bool isEventHandleable )
{
	// Set coordinates of window
	int32_t x = wndStyle.x;
	int32_t y = wndStyle.y;

	if ( wndStyle.ShowMiddle )
	{
		x = static_cast< int32_t >(
			GetSystemMetrics( SM_CXSCREEN )*0.5 -
			wndStyle.width*0.5 );
		y = static_cast< int32_t >(
			GetSystemMetrics( SM_CYSCREEN )*0.5 -
			wndStyle.height*0.5 );
	}


	// Convert WindowStyle to platform-dependent style.
	DWORD normalStyle, exStyle;
	Convert_wndstyle_to_dword( wndStyle, &exStyle, &normalStyle );


	// Register Window class to Global table.
	std::wstring newClassName;
	bool isSucceed = this->RegisterMyClass( wndStyle, &newClassName, isEventHandleable );
	if ( !isSucceed )
	{
		MessageBoxW(
			this->GetWindowHandle( ),
			L"Failed to invoke tgon::WindowsWindow::RegisterMyClass.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION );

		abort( );
	}


	// Convert utf8 to utf16
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
	std::wstring utf16Dest( converter.from_bytes( wndStyle.title.c_str( )));


	// Create a Window.
	m_wndHandle = CreateWindowExW(
		exStyle,
		newClassName.c_str(),
		utf16Dest.c_str( ),
		normalStyle,
		x, y, wndStyle.width, wndStyle.height,
		nullptr,
		nullptr,
		GetModuleHandle( NULL ),
		this
	);

	if ( !m_wndHandle )
	{
		MessageBoxW( 
			GetFocus( ),
			L"Failed to invoke CreateWindowEx.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);
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

bool tgon::WindowsWindow::RegisterMyClass( const WindowStyle& wndStyle, std::wstring* outClassName, bool isEventHandleable )
{
	const HINSTANCE instanceHandle( WindowsApplication::GetInstanceHandle( ));

	
	//	Each windows must have diffrent class name.
	std::wstring defClassName = L"TGON_Window";
	static int32_t numCreatedWindow = 0;
	defClassName += std::to_wstring( numCreatedWindow );
	*outClassName = defClassName;


	// Fill the Window class information.
	WNDCLASSEXW wcex {0};
	wcex.cbSize = sizeof( wcex );
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursorW( NULL, IDC_ARROW );
	wcex.hIcon = LoadIconW( NULL, IDI_APPLICATION );
	wcex.hInstance = instanceHandle;
	wcex.lpfnWndProc = ( isEventHandleable ) ?
		EvHandleMsgProc : 
		UnevHandleMsgProc; // Default message procedure; More fast than EvHandleMsgProc
	wcex.lpszClassName = defClassName.c_str( );
	wcex.style = CS_DBLCLKS;

	return RegisterClassExW( &wcex ) != 0;
}

LRESULT WINAPI tgon::WindowsWindow::EvHandleMsgProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	WindowsWindow* extraMemAsWindow = reinterpret_cast<WindowsWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
	{
		switch ( msg )
		{
		case WM_LBUTTONUP:
			extraMemAsWindow->OnLMouseUp( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_LBUTTONDOWN:
			extraMemAsWindow->OnLMouseDown( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_RBUTTONUP:
			extraMemAsWindow->OnRMouseUp( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_RBUTTONDOWN:
			extraMemAsWindow->OnRMouseDown( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_MOUSEMOVE:
			extraMemAsWindow->OnMouseMove( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_SIZE:
			extraMemAsWindow->OnSize( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_MOVE:
			extraMemAsWindow->OnMove( LOWORD( lParam ), HIWORD( lParam ));
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			extraMemAsWindow->m_isDestroyed = true;
			//extraMemAsWindow->->OnDestroy( );
			break;
		}
	}
	// Call the OnCreate event handler
	/*else if ( msg == WM_CREATE )
	{
		extraMemAsWindow = reinterpret_cast<WindowsWindow*>( LPCREATESTRUCT( 
			lParam )->lpCreateParams );
		extraMemAsWindow->OnCreate( );
	}*/

	return DefWindowProcW( wndHandle, msg, wParam, lParam );
}

LRESULT WINAPI tgon::WindowsWindow::UnevHandleMsgProc(
	HWND wndHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam )
{
	if ( msg == WM_DESTROY )
	{
		WindowsWindow* extraMemAsWindow = reinterpret_cast<WindowsWindow*>(
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

void tgon::WindowsWindow::GetWindowFormAccordingly( 
	const WindowStyle& wndStyle, 
	int32_t* x,
	int32_t* y )
{
}