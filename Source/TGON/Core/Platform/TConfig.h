/**
 * filename TConfig.h
 * author   ggomdyu
 * since    04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Private/Windows/WindowsConfig.h"
#elif BOOST_OS_ANDROID
#	include "Private/Android/AndroidConfig.h"
#elif BOOST_OS_IOS
#	include "Private/iOS/iOSConfig.h"
#endif

#ifndef TGON_SUPPORT_SSE2
#   define TGON_SUPPORT_SSE 0
#endif
#ifndef TGON_SUPPORT_NEON
#   define TGON_SUPPORT_NEON 0
#endif
#ifndef TGON_SUPPORT_SIMD
#   define TGON_SUPPORT_SIMD 0
#endif