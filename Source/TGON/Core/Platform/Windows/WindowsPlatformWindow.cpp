#include "PrecompiledHeader.h"
#include "WindowsPlatformWindow.h"

#include "WindowsPlatformWindowUtility.h"
#include "WindowsPlatformInclude.h"
#include "../OSAL/PlatformApplication.h"

#include <Windows.h>
#include <cassert>

#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


namespace tgon
{


WindowsPlatformWindow::WindowsPlatformWindow( const WindowStyle& wndStyle ) :
	m_wndHandle( CreateWindowForm( wndStyle, 
	   WindowsPlatformApplication::AppClassName, 
	   WindowsPlatformApplication::InstanceHandle ))
{
	// Initialization After window created ( Which needs a created window )
	this->AdditionalInit( wndStyle );
}

WindowsPlatformWindow::~WindowsPlatformWindow( )
{
	DestroyWindow( m_wndHandle );
}

bool WindowsPlatformWindow::PumpEvent( )
{
	MSG msg {0};
	if ( PeekMessageW( &msg, m_wndHandle, 0, 0, PM_REMOVE ) == TRUE )
	{
		// Pump WM_CHAR message
		//::TranslateMessage( &msg );

		// This will invke tgon::WindowsApplication::MessageProc each of events
		::DispatchMessageW( &msg );
		return true;
	}
	else
	{
		return false;
	}
}

void WindowsPlatformWindow::BringToFront( ) 
{
	// After Windows 98/Me: The system restricts which processes can set the foreground window.
	// So, you can't switch the focus freely by only SetFocus or SetForegroundWindow.

	DWORD currProcessId = GetWindowThreadProcessId( m_wndHandle, nullptr );
	DWORD foregroundProcessId = GetWindowThreadProcessId( GetForegroundWindow( ), nullptr );
	
	if ( AttachThreadInput( currProcessId, foregroundProcessId, TRUE ))
	{
		SetForegroundWindow( m_wndHandle );
		BringWindowToTop( m_wndHandle );
	
		AttachThreadInput( currProcessId, foregroundProcessId, TRUE );
	}
}

void WindowsPlatformWindow::Flash( )
{
	FLASHWINFO fwi {0};
	fwi.cbSize = sizeof( FLASHWINFO );
	fwi.dwFlags = FLASHW_CAPTION;
	fwi.dwTimeout = 0;
	fwi.hwnd = this->GetWindowHandle( );
	fwi.uCount = 1;

	FlashWindowEx( &fwi );
}

void WindowsPlatformWindow::EnableGlobalMouseFocus( bool isEnable )
{
	assert( m_wndHandle && "tgon::WindowsPlatformWindow::EnableGlobalMouseFocus must be invoked after window created!" );

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

void WindowsPlatformWindow::GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const
{
	// RECT contains caption range
	RECT rt;
	GetWindowRect( this->GetWindowHandle( ), &rt );

	*x = rt.left;
	*y = rt.top;
}

void WindowsPlatformWindow::GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const 
{
	// RECT contains caption range
	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	*width = rt.right;
	*height = rt.bottom;
}

void WindowsPlatformWindow::GetCaption( /*Out*/ wchar_t* caption ) const
{
	const int32_t length = GetWindowTextLengthW( m_wndHandle );
	GetWindowTextW( m_wndHandle, caption, length );
}

HWND WindowsPlatformWindow::GetWindowHandle( ) const
{
	return m_wndHandle;
}

void WindowsPlatformWindow::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}

void WindowsPlatformWindow::Hide( )
{
	ShowWindow( m_wndHandle, SW_HIDE );
}

void WindowsPlatformWindow::Maximize( )
{
	ShowWindow( m_wndHandle, SW_MAXIMIZE );
}

void WindowsPlatformWindow::Minimize( )
{
	ShowWindow( m_wndHandle, SW_MINIMIZE );
}

void WindowsPlatformWindow::Quit( )
{
	PostQuitMessage( 0 );
}

void WindowsPlatformWindow::SetPosition( int32_t x, int32_t y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

void WindowsPlatformWindow::SetScale( int32_t width, int32_t height ) 
{
	SetWindowPos( m_wndHandle, nullptr, 0, 0, width, height, SWP_NOMOVE );
}

void WindowsPlatformWindow::SetCaption( const wchar_t* caption )
{
	SetWindowTextW( m_wndHandle, caption );
}

void WindowsPlatformWindow::AdditionalInit( const WindowStyle& wndStyle ) 
{
	// Save this class pointer to storage.
	// Then accessible this class even static function.
	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>( this )
	);

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

LRESULT WindowsPlatformWindow::ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( !m_eventListener )
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}

	switch ( msg )
	{
	case WM_SETFOCUS:
		{
			if ( !m_eventListener->OnGetFocus( ))
			{
				// Ignore window focus
				return 0;
			}
		}
		break;

	case WM_KILLFOCUS:
		{
			if ( !m_eventListener->OnLoseFocus( ))
			{
				// Ignore window focus
				return -1;
			}
		}
		break;

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
				// Ignore window destroying process
				return 0;
			}
		}
		// or, keep process
		break;
				
	case WM_DESTROY:
		{
			m_closed = true;
			PostQuitMessage( 0 );
		}
		return 0;

	case WM_LBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
		}
		return 0;

	case WM_LBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
			return 0;
		}
		break;

	case WM_RBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_RBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_MBUTTONDOWN:
		{
			m_eventListener->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
			);
			return 0;
		}
		break;

	case WM_MBUTTONUP:
		{
			m_eventListener->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
			);
			return 0;
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
			return 0;
		}
		break;
		
	case WM_RBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_MBUTTONDBLCLK:
		{
			m_eventListener->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
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


} /*namespace tgon*/