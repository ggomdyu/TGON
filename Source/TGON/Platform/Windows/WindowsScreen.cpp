#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "../Screen.h"

namespace tgon
{
namespace
{

Screen ConvertDEVMODEToScreen(const DEVMODE& dm) noexcept
{
    static constexpr const ScreenOrientation nativeScreenOrientationTable[4]
    {
        ScreenOrientation::Landscape, // DMDO_DEFAULT
        ScreenOrientation::Portrait,
    };

    return Screen(
        dm.dmPelsWidth,
        dm.dmPelsHeight,
        static_cast<int16_t>(dm.dmBitsPerPel),
        static_cast<int16_t>(dm.dmDisplayFrequency),
        nativeScreenOrientationTable[dm.dmDisplayOrientation],
        false
    );
}

} /* namespace */

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

int32_t GetScreenCount()
{
    return GetSystemMetrics(SM_CMONITORS);
}

TGON_API Screen GetPrimaryScreen()
{
    DEVMODE deviceMode {};
    deviceMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &deviceMode);

    return ConvertDEVMODEToScreen(deviceMode);
}

std::vector<Screen> GetAllScreen()
{
    std::vector<Screen> screens;

    DWORD deviceIndex = 0;

    DISPLAY_DEVICE dd {};
    dd.cb = sizeof(DISPLAY_DEVICE);
    while (EnumDisplayDevices(NULL, deviceIndex++, &dd, 0) == TRUE)
    {
        DISPLAY_DEVICE displayMonitorDevice {};
        displayMonitorDevice.cb = sizeof(DISPLAY_DEVICE);

        // Iterate all monitor devices.
        DWORD monitorDeviceIndex = 0;
        while (EnumDisplayDevices(dd.DeviceName, monitorDeviceIndex++, &displayMonitorDevice, 0) == TRUE)
        {
            if ((displayMonitorDevice.StateFlags & DISPLAY_DEVICE_ACTIVE) == false)
            {
                continue;
            }

            DEVMODE dm {};
            dm.dmSize = sizeof(DEVMODE);
            EnumDisplaySettingsW(displayMonitorDevice.DeviceName, ENUM_CURRENT_SETTINGS, &dm);

            screens.push_back(ConvertDEVMODEToScreen(dm));
        }
    }

    return screens;
}

} /* namespace tgon */
