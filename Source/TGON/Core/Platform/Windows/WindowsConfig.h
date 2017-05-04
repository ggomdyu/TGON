/**
 * @filename    WindowsConfig.h
 * @author   ggomdyu
 * since    04/24/2016
 */

#pragma once
#define TGON_USING_LITTLE_ENDIAN

#define TGON_SUPPORT_SSE2
#define TGON_SUPPORT_SIMD
#include <intrin.h>

#if (WINVER >= _WIN32_WINNT_VISTA)
#	define TGON_SUPPORT_DWMAPI
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