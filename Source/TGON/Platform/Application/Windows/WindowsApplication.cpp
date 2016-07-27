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

tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	adapter.hasBattery = ( sps.BatteryFlag == 128 ) ? false : true;
	adapter.batteryLifePercent = sps.BatteryLifePercent;

	return adapter;
}

bool tgon::WindowsApplication::RegisterClass( )
{
	WNDCLASSEXW wcex {0};

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
	WindowsWindow* extraMemAsWindow = WindowsApplication::GetWindowFromHWND( wndHandle );
	
	if ( extraMemAsWindow )
	{
		return extraMemAsWindow->ProcessMessage( wndHandle, msg, wParam, lParam );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}

