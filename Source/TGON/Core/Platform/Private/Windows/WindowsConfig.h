/**
 * filename WindowsConfig.h
 * author   ggomdyu
 * since    04/24/2016
 */

#pragma once
#include <boost/predef/os.h>

/**
 * brief    SIMD support flag
 */
#define TGON_SUPPORT_SSE2 1
#define TGON_SUPPORT_SIMD 1
#include <intrin.h>

/**
 *  brief    DWM support flag
 */
#if (WINVER >= _WIN32_WINNT_VISTA)
#	define TGON_SUPPORT_DWMAPI 1
#else
#	define TGON_SUPPORT_DWMAPI 0
#endif

#ifdef _WINDLL
#	ifdef TGON_API_EXPORT
#		define TGON_API __declspec(dllexport)
#	else
#		define TGON_API __declspec(dllimport)
#	endif
#else
#	define TGON_API
#endif