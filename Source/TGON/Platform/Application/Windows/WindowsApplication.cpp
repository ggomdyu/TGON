#include "PrecompiledHeader.h"
#include "WindowsApplication.h"


#include "../../Window/TWindow.h"


const wchar_t* tgon::WindowsApplication::AppClassName = L"TGON_Application";


tgon::WindowsApplication::WindowsApplication( )
{
	this->RegisterClass( );
}

tgon::WindowsApplication::~WindowsApplication( )
{
}

bool tgon::WindowsApplication::PumpEvent( )
{
	MSG msg {0};

	if ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) == TRUE )
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

tgon::TBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TBatteryInfo adapter;
	adapter.hasBattery = ( sps.BatteryFlag == 128 ) ? false : true;
	adapter.batteryLifePercent = sps.BatteryLifePercent;

	return adapter;
}

bool tgon::WindowsApplication::ToggleFullScreen( const AbstractWindow& window )
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

bool tgon::WindowsApplication::RegisterClass( )
{
	WNDCLASSEXW wcex {};

	wcex.cbSize = sizeof( wcex );
	wcex.lpszClassName = WindowsApplication::AppClassName;
	wcex.style = CS_DBLCLKS;
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursorW( NULL, IDC_ARROW );
	wcex.hIcon = LoadIconW( NULL, IDI_APPLICATION );
	wcex.hInstance = WindowsApplication::GetInstanceHandle( );
	wcex.lpfnWndProc = WindowsApplication::MessageProc; // Default message procedure; More fast than EvHandleMsgProc

	return RegisterClassExW( &wcex ) != 0;
}

LRESULT WINAPI tgon::WindowsApplication::MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	WindowsWindow* extraMemAsWindow = reinterpret_cast<WindowsWindow*>( 
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

