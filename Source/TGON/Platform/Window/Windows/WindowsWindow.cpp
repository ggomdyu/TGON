#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "../Platform/Slate/PlatformApplication.h"
#include "../Platform/Slate/PlatformProperty.h"
#include "../../Window/WindowStyle.h"
#include "../../Window/Windows/WindowsWindowUtility.h"
#include "../../Application/TApplication.h"

#include <Windows.h>
#include <cassert>
#include <codecvt>

#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


tgon::WindowsWindow::WindowsWindow( const WindowStyle& wndStyle ) :
	m_wndHandle( nullptr )
{
	this->CreateWindowForm( wndStyle );

	// Initialization After window created ( Which needs a created window )
	this->AdditionalInit( wndStyle );
}

tgon::WindowsWindow::~WindowsWindow( )
{
	DestroyWindow( m_wndHandle );
}

bool tgon::WindowsWindow::PumpEvent( )
{
	MSG msg {0};

	if ( PeekMessageW( &msg, m_wndHandle, 0, 0, PM_REMOVE ) == TRUE )
	{
		// To Process WM_CHAR
		::TranslateMessage( &msg );

		// This will invke tgon::WindowsApplication::MessageProc each of events
		::DispatchMessageW( &msg );
		return true;
	}
	else
	{
		return false;
	}
}

void tgon::WindowsWindow::BringToTop( ) 
{
	// After Windows 98/Me: The system restricts which processes can set the foreground window.
	// So, you can't switch the focus freely by only SetFocus or SetForegroundWindow.

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

void tgon::WindowsWindow::EnableGlobalMouseFocus( bool isEnable )
{
	assert( m_wndHandle && "tgon::WindowsWindow::EnableGlobalMouseFocus must be invoked after window created!" );

	m_enabledGlobalMouseFocus = isEnable;


	enum class RawInputDeviceType : USHORT
	{
		kPointer = 0x01,
		kMouse = 0x02,
		kJoyStick = 0x04,
		kGamePad = 0x05,
		kKeyboard = 0x06,
		kKeyPad = 0x07,
	};

	RAWINPUTDEVICE rid {0};

	rid.usUsagePage = 0x01;
	rid.usUsage = static_cast<USHORT>( RawInputDeviceType::kMouse );
	rid.dwFlags = ( isEnable ) ? RIDEV_INPUTSINK : RIDEV_REMOVE;
	rid.hwndTarget = this->GetWindowHandle( );
	

	if ( ::RegisterRawInputDevices( &rid, 1, sizeof( RAWINPUTDEVICE )) == FALSE )
	{
		MessageBoxW( 
			this->GetWindowHandle( ),
			L"Failed to initialize global input focus.",
			L"WARNINIG!",
			MB_OK 
		);
	}
}

void tgon::WindowsWindow::GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const
{
	// RECT contains caption range
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void tgon::WindowsWindow::GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const 
{
	// RECT contains caption range
	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	*width = rt.right;
	*height = rt.bottom;
}

void tgon::WindowsWindow::GetCaption( /*Out*/ wchar_t* caption ) const
{
	const int32_t length = GetWindowTextLengthW( m_wndHandle );
	GetWindowTextW( m_wndHandle, caption, length );
}

void tgon::WindowsWindow::CreateWindowForm( /*In*/ const WindowStyle& wndStyle )
{
	// Set coordinates of window
	int32_t x = wndStyle.x;
	int32_t y = wndStyle.y;

	if ( wndStyle.showMiddle )
	{
		x = static_cast<int32_t>( GetSystemMetrics( SM_CXSCREEN )*0.5 - wndStyle.width*0.5 );
		y = static_cast<int32_t>( GetSystemMetrics( SM_CYSCREEN )*0.5 - wndStyle.height*0.5 );
	}

	// Convert WindowStyle to platform dependent style.
	DWORD normalStyle, exStyle;
	ConvertWindowStyleToDword( wndStyle, &exStyle, &normalStyle );
	
	// Convert utf8 encoded title to utf16.
	// This string encoding converter shows bad performance.
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
	std::wstring utf16Title( utfConverter.from_bytes( wndStyle.title.c_str( )));

	// Create a Window.
	m_wndHandle = CreateWindowExW(
		exStyle,
		TApplication::AppClassName,
		utf16Title.c_str( ),
		// WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our Window.
		normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x,
		y, 
		wndStyle.width, 
		wndStyle.height,
		nullptr,	// No parent ( Unsupported now )
		nullptr,	// No menu ( Unsupported now )
		TApplication::Get( )->GetInstanceHandle( ),
		nullptr		// No extra parameter
	);

	// Is failed to create window?
	if ( !m_wndHandle )
	{
		// Then, show error message.
		MessageBoxW( nullptr,
			L"Failed to invoke CreateWindowEx.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);

		std::abort( );
	}

	// Save this class pointer to storage.
	// Then accessible this class even static function.
	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>( this )
	); 
}

void tgon::WindowsWindow::AdditionalInit( const WindowStyle& wndStyle ) 
{
	if ( wndStyle.supportWindowTransparency )
	{
		SetLayeredWindowAttributes( m_wndHandle, NULL, 255, LWA_ALPHA );
	}

#ifdef TGON_SUPPORT_DWMAPI
	if ( wndStyle.supportPerPixelTransparency )
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

LRESULT tgon::WindowsWindow::ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( !m_eventListener )
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}

	switch ( msg )
	{
	case WM_MOVE:
		{
			m_eventListener->OnMove(
				static_cast<int32_t>( LOWORD( lParam )), 
				static_cast<int32_t>( HIWORD( lParam ))
			);
		}
		return 0;

	case WM_SIZE:
		{
			m_eventListener->OnResize(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam ))
			);
		}
		return 0;

	case WM_CLOSE:
		{
			if ( !m_eventListener->OnDestroy( ))
			{
				return 0;
			}
		}
		break;
				
	case WM_DESTROY:
		{
			m_destroyed = true;
			PostQuitMessage( 0 );
		}
		return 0;

	case WM_LBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kLeft
			);
		}
		return 0;

	case WM_LBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kLeft
			);
			return 0;
		}
		break;

	case WM_RBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kRight
			);
			return 0;
		}
		break;

	case WM_RBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kRight
			);
			return 0;
		}
		break;

	case WM_MBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kMiddle
			);
			return 0;
		}
		break;

	case WM_MBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kMiddle
			);
			return 0;
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kLeft
			);
			return 0;
		}
		break;
		
	case WM_RBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kRight
			);
			return 0;
		}
		break;

	case WM_MBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				TMouseType::kMiddle
			);
			return 0;
		}
		break;

	case WM_MOUSEMOVE:
		{
			m_eventListener->OnMouseMove(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam ))
			);
			return 0;
		}
		break;

	case WM_INPUT:
		{
			RAWINPUT rawInput{ 0 };

			UINT cbSize = sizeof( RAWINPUT );
			::GetRawInputData( reinterpret_cast<HRAWINPUT>( lParam ), RID_INPUT, &rawInput, &cbSize, sizeof( RAWINPUTHEADER ) );

			if ( rawInput.header.dwType == RIM_TYPEMOUSE )
			{
				if ( rawInput.data.mouse.usButtonFlags == 0 )
				{
				}
				else if ( rawInput.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN )
				{
				}
				else if ( rawInput.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP )
				{
				}
			}

			return 0;
		}
		break;
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}
