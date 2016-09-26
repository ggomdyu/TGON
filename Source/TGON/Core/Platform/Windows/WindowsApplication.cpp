#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../Windows/WindowsWindowFrame.h"


namespace tgon
{


const HINSTANCE WindowsApplication::InstanceHandle = GetModuleHandle( nullptr );
const wchar_t* WindowsApplication::AppClassName = L"TGON";


bool WindowsApplication::PumpEvent( )
{
	MSG msg {0};
	if ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) == TRUE )
	{
		// To Process WM_CHAR
		::TranslateMessage( &msg );

		// This will invke tgon::WindowsPlatformApplication::MessageProc each of events
		::DispatchMessageW( &msg );
		return true;
	}
	else
	{
		return false;
	}
}

BatteryProperty WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	BatteryProperty adapter {
		sps.BatteryFlag == 128 ? false : true,
		sps.BatteryLifePercent
	};

	return adapter;
}

bool WindowsApplication::ToggleFullScreen( const GenericWindowFrame& window )
{
	return false;

	//// Get the monitor info from the window handle.
	//HMONITOR hMonitor = MonitorFromWindow( Context->WindowHandle, MONITOR_DEFAULTTOPRIMARY );
	//MONITORINFOEX MonitorInfo;
	//memset( &MonitorInfo, 0, sizeof( MONITORINFOEX ));
	//MonitorInfo.cbSize = sizeof( MONITORINFOEX );
	//GetMonitorInfo( hMonitor, &MonitorInfo );
	//
	//DEVMODE dmScreenSettings{ 0 };
	//dmScreenSettings.dmSize = sizeof( dmScreenSettings );
	//dmScreenSettings.dmPelsWidth = 1;
	//dmScreenSettings.dmPelsHeight = 1;
	//dmScreenSettings.dmBitsPerPel = 32;
	//dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	//
	//
	//return ( ChangeDisplaySettingsEx( &dmScreenSettings, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) ? true : false;
}

LRESULT WINAPI WindowsApplication::OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	WindowsWindowFrame* extraMemAsWindow = reinterpret_cast<WindowsWindowFrame*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));
	
	if ( extraMemAsWindow )
	{
		return extraMemAsWindow->OnMessageHandled( wndHandle, msg, wParam, lParam );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}

void WindowsApplication::ExitThread( int32_t exitCode )
{
	::ExitThread( exitCode );
}

void WindowsApplication::Quit( int32_t exitCode )
{
	PostQuitMessage( exitCode );
}

void WindowsApplication::ShowCursor( bool enableShow )
{
	::ShowCursor(( enableShow ) ? TRUE : FALSE );
}


} /*namespace tgon*/
