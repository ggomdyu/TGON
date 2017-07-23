/**
 * @filename    Screen.h
 * @author      ggomdyu
 * @since       07/05/2016
 */

#pragma once
#include <cstdint>
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsScreen.h"
#if BOOST_OS_ANDROID
#	include "Android/AndroidScreen.h"
#if BOOST_OS_IOS
#	include "IOS/IOSScreen.h"
#endif

namespace tgon
{
namespace platform
{

TGON_API int32_t GetMonitorCount();

TGON_API void GetScreenResolution(int32_t* width, int32_t* height);

TGON_API float GetScaleFactor();

} /* namespace platform */
} /* namespace tgon */
