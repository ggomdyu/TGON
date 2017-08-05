#include "PrecompiledHeader.pch"

#include <Windows.h>

#include "WindowsScreen.h"

namespace tgon
{
namespace platform
{

//bool WindowsScreen::SetFullScreen(bool setFullScreen, const WindowsWindow& window)
//{
//	return false;
//
//	//// Get the monitor info from the window handle.
//	//HMONITOR hMonitor = MonitorFromWindow( Context->WindowHandle, MONITOR_DEFAULTTOPRIMARY );
//	//MONITORINFOEX MonitorInfo;
//	//memset( &MonitorInfo, 0, sizeof( MONITORINFOEX ));
//	//MonitorInfo.cbSize = sizeof( MONITORINFOEX );
//	//GetMonitorInfo( hMonitor, &MonitorInfo );
//	//
//	//DEVMODE dmScreenSettings{ 0 };
//	//dmScreenSettings.dmSize = sizeof( dmScreenSettings );
//	//dmScreenSettings.dmPelsWidth = 1;
//	//dmScreenSettings.dmPelsHeight = 1;
//	//dmScreenSettings.dmBitsPerPel = 32;
//	//dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
//	//
//	//
//	//return ( ChangeDisplaySettingsEx( &dmScreenSettings, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) ? true : false;
//}

int32_t GetMonitorCount()
{
    return GetSystemMetrics(SM_CMONITORS);
}

TGON_API void GetScreenResolution(int32_t* width, int32_t* height)
{
	*width = static_cast<int32_t>(GetSystemMetrics(SM_CXSCREEN));
	*height = static_cast<int32_t>(GetSystemMetrics(SM_CYSCREEN));
}

} /* namespace platform */
} /* namespace tgon */