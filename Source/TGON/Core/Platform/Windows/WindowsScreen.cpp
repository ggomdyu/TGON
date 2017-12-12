#include "PrecompiledHeader.pch"
#include "../Screen.h"

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{
namespace platform
{
namespace
{

Screen ConvertDEVMODEToScreen(const DEVMODE& dm)
{
    static constexpr const ScreenOrientation nativeDisplayOrientationConversionTable[4]
    {
        ScreenOrientation::Landscape, // 0
        ScreenOrientation::Portrait, // 1
    };

    return Screen(
        dm.dmPelsWidth,
        dm.dmPelsHeight,
        static_cast<int16_t>(dm.dmBitsPerPel),
        static_cast<int16_t>(dm.dmDisplayFrequency),
        nativeDisplayOrientationConversionTable[dm.dmDisplayOrientation],
        false
    );
}

}

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

TGON_API Screen GetMainScreen()
{
    DEVMODE dm {};
    dm.dmSize = sizeof(DEVMODE);

    EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &dm);

    return ConvertDEVMODEToScreen(dm);
}

//std::vector<Screen> GetAllScreen()
//{
//    std::vector<Screen> screens;
//
//    DISPLAY_DEVICE displayDevice {};
//    displayDevice.cb = sizeof(DISPLAY_DEVICE);
//
//    DWORD deviceIndex = 0;
//    while (EnumDisplayDevices(NULL, deviceIndex++, &displayDevice, 0) == TRUE)
//    {
//        DISPLAY_DEVICE displayMonitorDevice {};
//        displayMonitorDevice.cb = sizeof(DISPLAY_DEVICE);
//
//        // Iterate all monitor devices.
//        DWORD monitorDeviceIndex = 0;
//        while (EnumDisplayDevices(displayDevice.DeviceName, monitorDeviceIndex++, &displayMonitorDevice, 0) == TRUE)
//        {
//            if ((displayMonitorDevice.StateFlags & DISPLAY_DEVICE_ACTIVE) == false)
//            {
//                continue;
//            }
//
//            DEVMODE dm{};
//            dm.dmSize = sizeof(DEVMODE);
//
//            EnumDisplaySettingsW(displayMonitorDevice.DeviceName, ENUM_CURRENT_SETTINGS, &dm);
//
//            screens.emplace_back(
//                dm.dmPelsWidth,
//                dm.dmPelsHeight,
//                dm.dmBitsPerPel,
//                dm.dmDisplayFrequency,
//                ConvertNativeToScreenOrientation(dm)
//            );
//        }
//    }
//
//    return screens;
//}

} /* namespace platform */
} /* namespace tgon */
