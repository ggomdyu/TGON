#include "PrecompiledHeader.h"
#include "WindowsWindowFrame.h"

#include "WindowsWindowUtility.h"
#include "WindowsInclude.h"
#include "WindowsApplication.h"

#include <Windows.h>
#include <cassert>

#ifdef TGON_SUPPORT_DWMAPI
	#include <dwmapi.h>
	#pragma comment( lib, "dwmapi.lib" )
#endif


namespace tgon
{


WindowsWindowFrame::WindowsWindowFrame( _In_ const WindowStyle& wndStyle ) :
	m_enabledGlobalInputHook( false ),
	m_wndHandle( CreateWindowForm( wndStyle, WindowsApplication::AppClassName, WindowsApplication::InstanceHandle ))
{
	DragAcceptFiles( m_wndHandle, true );

	// Setup Transparency support
	this->AdditionalInit( wndStyle );
}

WindowsWindowFrame::~WindowsWindowFrame( )
{
	this->Release( );
	DestroyWindow( m_wndHandle );
}

bool WindowsWindowFrame::PumpEvent( )
{
	MSG msg {0};
	if ( PeekMessageW( &msg, m_wndHandle, 0, 0, PM_REMOVE ) == TRUE )
	{
		// Pump WM_CHAR message
		//::TranslateMessage( &msg );

		// This will invoke tgon::WindowsApplication::OnMessageHandled
		::DispatchMessageW( &msg );
		return true;
	}
	else
	{
		return false;
	}
}

void WindowsWindowFrame::BringToFront( ) 
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

void WindowsWindowFrame::Flash( )
{
	FLASHWINFO fwi {0};
	fwi.cbSize = sizeof( FLASHWINFO );
	fwi.dwFlags = FLASHW_CAPTION;
	fwi.dwTimeout = 0;
	fwi.hwnd = m_wndHandle;
	fwi.uCount = 1;

	FlashWindowEx( &fwi );
}

bool WindowsWindowFrame::IsEnabledGlobalInputHook( ) const
{
	return m_enabledGlobalInputHook;
}

void WindowsWindowFrame::GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	*x = rt.left;
	*y = rt.top;
}

void WindowsWindowFrame::GetSize( 
	/*Out*/ int32_t* width, 
	/*Out*/ int32_t* height ) const 
{
	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	*width = rt.right;
	*height = rt.bottom;
}

void WindowsWindowFrame::GetCaptionText( 
	/*Out*/ wchar_t* dest ) const
{
	int32_t length = GetWindowTextLengthW( m_wndHandle );
	GetWindowTextW( m_wndHandle, dest, length );
}

HWND WindowsWindowFrame::GetWindowHandle() const
{
	return m_wndHandle;
}

STDMETHODIMP WindowsWindowFrame::QueryInterface( 
	REFIID riid, 
	void** ppvObject )
{
	if ( riid == IID_IUnknown || riid == IID_IDropTarget )
	{
		*ppvObject = static_cast<IUnknown*>( this );
		this->AddRef( );
		return S_OK;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
}

STDMETHODIMP_( ULONG ) WindowsWindowFrame::AddRef( )
{
	return ++m_comRefCount;
}

STDMETHODIMP_( ULONG ) WindowsWindowFrame::Release( )
{
	if ( --m_comRefCount == 0 )
	{
		delete this;
		return 0;
	}
	return m_comRefCount;
}

STDMETHODIMP WindowsWindowFrame::DragEnter( 
	LPDATAOBJECT pDataObj, 
	DWORD grfKeyState, 
	POINTL pt, 
	LPDWORD pdwEffect )
{
	return E_NOTIMPL;
}

STDMETHODIMP WindowsWindowFrame::DragOver( 
	DWORD grfKeyState, 
	POINTL pt, 
	LPDWORD pdwEffect )
{
	return E_NOTIMPL;
}

void WindowsWindowFrame::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}

void WindowsWindowFrame::Hide( )
{
	ShowWindow( m_wndHandle, SW_HIDE );
}

void WindowsWindowFrame::Maximize( )
{
	ShowWindow( m_wndHandle, SW_MAXIMIZE );
}

void WindowsWindowFrame::Minimize( )
{
	ShowWindow( m_wndHandle, SW_MINIMIZE );
}

void WindowsWindowFrame::Quit( )
{
	PostQuitMessage( 0 );
}

void WindowsWindowFrame::SetPosition( 
	int32_t x, 
	int32_t y )
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

void WindowsWindowFrame::SetScale( 
	int32_t width, 
	int32_t height ) 
{
	SetWindowPos( m_wndHandle, nullptr, 0, 0, width, height, SWP_NOMOVE );
}

void WindowsWindowFrame::SetCaption( 
	const wchar_t* caption )
{
	SetWindowTextW( m_wndHandle, caption );
}

DWORD WindowsWindowFrame::EnableGlobalInputHook( bool isEnable, RawInputType inputFlag )
{
	m_enabledGlobalInputHook = isEnable;

	assert( false && "DO NOT INVOKE EnableGlobalInputHook" );


	RAWINPUTDEVICE rawInputDeviceInfo {};
	rawInputDeviceInfo.usUsagePage = 0x01;
	rawInputDeviceInfo.usUsage = inputFlag;
	rawInputDeviceInfo.dwFlags = ( isEnable ) ? RIDEV_INPUTSINK : RIDEV_REMOVE;
	rawInputDeviceInfo.hwndTarget = m_wndHandle;

	const BOOL succeed = ::RegisterRawInputDevices( &rawInputDeviceInfo, 1, sizeof( RAWINPUTDEVICE ));
	if ( succeed == FALSE )
	{
		DWORD lastError = GetLastError( );

		MessageBoxW( 
			m_wndHandle,
			L"Failed to invoke ::RegisterRawInputDevices.",
			L"WARNINIG!",
			MB_OK 
		);

		return lastError;
	}

	return 0;
}

HRESULT WindowsWindowFrame::DragLeave( )
{
	return S_OK;
}

STDMETHODIMP WindowsWindowFrame::Drop( 
	LPDATAOBJECT pDataObj, 
	DWORD grfKeyState, 
	POINTL pt, 
	LPDWORD pdwEffect )
{
	return E_NOTIMPL;
}

void WindowsWindowFrame::AdditionalInit( 
	const WindowStyle& wndStyle )
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

LRESULT WindowsWindowFrame::OnMessageHandled( 
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_CREATE:
		/* DO NOT HANDLE THIS MESSAGE */
		break;

	case WM_SETFOCUS:
		{
			if ( !this->OnGetFocus( ))
			{
				// Ignore window focus
				return 0;
			}
		}
		break;

	case WM_KILLFOCUS:
		{
			if ( !this->OnLoseFocus( ))
			{
				// Ignore window focus
				return -1;
			}
		}
		break;

	case WM_MOVE:
		{
			this->OnMove(
				static_cast<int32_t>( LOWORD( lParam )), 
				static_cast<int32_t>( HIWORD( lParam ))
			);
		}
		return 0;

	case WM_SIZE:
		{
			this->OnResize(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam ))
			);
		}
		return 0;

	case WM_CLOSE:
		{
			if ( !this->OnDestroy( ))
			{
				// Ignore window destroying process
				return 0;
			}
		}
		// or, keep destroying
		break;
				
	case WM_DESTROY:
		{
			m_closed = true;
			PostQuitMessage( 0 );
		}
		return 0;

	case WM_LBUTTONDOWN:
		{
			this->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
		}
		return 0;

	case WM_LBUTTONUP:
		{
			this->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
			return 0;
		}
		break;

	case WM_RBUTTONDOWN:
		{
			this->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_RBUTTONUP:
		{
			this->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_MBUTTONDOWN:
		{
			this->OnMouseDown(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
			);
			return 0;
		}
		break;

	case WM_MBUTTONUP:
		{
			this->OnMouseUp(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
			);
			return 0;
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			this->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Left
			);
			return 0;
		}
		break;
		
	case WM_RBUTTONDBLCLK:
		{
			this->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Right
			);
			return 0;
		}
		break;

	case WM_MBUTTONDBLCLK:
		{
			this->OnMouseDoubleClick(
				static_cast<int32_t>( LOWORD( lParam )),
				static_cast<int32_t>( HIWORD( lParam )),
				MouseType::Middle
			);
			return 0;
		}
		break;

	case WM_MOUSEMOVE:
		{
			this->OnMouseMove(
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


} /* namespace tgon */
