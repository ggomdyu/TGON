#pragma once
#include <boost/predef/os.h>

#if !BOOST_OS_WINDOWS
#   error "WindowsPlatformInclude.h included but BOOST_OS_WINDOWS is not defined"
#endif

//
//  SIMD
//
#define TGON_SUPPORT_SSE2 1
#define TGON_SUPPORT_SIMD 1
#include <intrin.h>

//
//  DWM
//
#if ( WINVER >= _WIN32_WINNT_VISTA ) 
#	define TGON_SUPPORT_DWMAPI 1
#else
#	define TGON_SUPPORT_DWMAPI 0
#endif