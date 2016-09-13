#include "PrecompiledHeader.h"
#include "WindowsPlatformApplication.h"

#include "../Windows/WindowsPlatformWindow.h"


namespace tgon
{


const HINSTANCE WindowsPlatformApplication::InstanceHandle = GetModuleHandle( nullptr );
const wchar_t* WindowsPlatformApplication::AppClassName = L"TGON";


WindowsPlatformApplication::WindowsPlatformApplication( )
{
	RegisterClass( );
}

bool WindowsPlatformApplication::PumpEvent( )
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

BatteryProperty WindowsPlatformApplication::GetPowerInfo( ) const
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	BatteryProperty adapter;
	adapter.hasBattery = ( sps.BatteryFlag == 128 ) ? false : true;
	adapter.batteryLifePercent = sps.BatteryLifePercent;

	return adapter;
}

bool WindowsPlatformApplication::ToggleFullScreen( const APlatformWindow& window )
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

bool WindowsPlatformApplication::RegisteClass( )
{
	WNDCLASSEXW wcex {};

	wcex.cbSize = sizeof( wcex );
	wcex.lpszClassName = WindowsPlatformApplication::AppClassName;
	wcex.style = CS_DBLCLKS;
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursorW( NULL, IDC_ARROW );
	wcex.hIcon = LoadIconW( NULL, IDI_APPLICATION );
	wcex.hInstance = WindowsPlatformApplication::InstanceHandle;
	wcex.lpfnWndProc = WindowsPlatformApplication::MessageProc; // Default message procedure; More fast than EvHandleMsgProc

	return RegisterClassExW( &wcex ) != 0;
}

LRESULT WINAPI WindowsPlatformApplication::MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	WindowsPlatformWindow* extraMemAsWindow = reinterpret_cast<WindowsPlatformWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));
	
	if ( extraMemAsWindow )
	{
		return extraMemAsWindow->ProcessMessage( wndHandle, msg, wParam, lParam );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}

void WindowsPlatformApplication::ExitThread( int32_t exitCode )
{
	::ExitThread( exitCode );
}

void WindowsPlatformApplication::Quit( int32_t exitCode )
{
	PostQuitMessage( exitCode );
}

void WindowsPlatformApplication::ShowCursor( bool enableShow )
{
	::ShowCursor(( enableShow ) ? TRUE : FALSE );
}


} /*namespace tgon*/
