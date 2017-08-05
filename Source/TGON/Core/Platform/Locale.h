/**
 * @filename    Locale.h
 * @author      ggomdyu
 * @since       06/14/2017
 */

#pragma once
#include <cstdint>
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsLocale.h"
#elif BOOST_OS_MACOS
#	import "MacOS/MacOSLocale.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidLocale.h"
#elif BOOST_OS_IOS
#	import "IOS/IOSLocale.h"
#endif

namespace tgon
{
namespace platform
{

/**
 * @brief                       Get the current language of OS.
 * @param [out] destBuffer      The destination of the string to be written.
 * @param [in] bufferLength     The length of buffer
 */
void GetLanguage(char* destBuffer, std::size_t bufferLength);

template <std::size_t N>
inline void GetLanguage(char(&destBuffer)[N])
{
    GetLanguage(destBuffer, N);
}

} /* namespace platform */
} /* namespace tgon */