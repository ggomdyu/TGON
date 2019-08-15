/**
 * @file    Config.h
 * @author  ggomdyu
 * @since   04/01/2016
 * @see     https://sourceforge.net/p/predef/wiki/OperatingSystems/
 */

#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#   include "Windows/WindowsConfig.h"
#elif defined(__APPLE__)
#   if defined(TARGET_OS_MAC) || defined(macintosh) || defined(Macintosh) || defined(__MACH__)
#       import "MacOS/MacOSConfig.h"
#   elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#       import "IOS/IOSConfig.h"
#   endif
#elif defined(__ANDROID__) || defined(__ANDROID_API__)
#   include "Android/AndroidConfig.h"
#endif