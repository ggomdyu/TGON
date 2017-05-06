#include "PrecompiledHeader.h"
#include "WindowsScreen.h"

#include <Windows.h>
#include "WindowsWindow.h"

namespace tgon {
namespace platform {

bool WindowsScreen::SetFullScreen(bool setFullScreen, const WindowsWindow& window)
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

int32_t WindowsScreen::GetMonitorCount()
{
    return GetSystemMetrics(SM_CMONITORS);
}

int32_t WindowsScreen::GetResolutionWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int32_t WindowsScreen::GetResolutionHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

} /* namespace platform */
} /* namespace tgon */