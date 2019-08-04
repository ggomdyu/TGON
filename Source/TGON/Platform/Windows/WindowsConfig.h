/**
 * @file    WindowsConfig.h
 * @author  ggomdyu
 * @since   04/24/2016
 */

#pragma once

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#define TGON_PLATFORM_NAME Windows
#define TGON_PLATFORM_WINDOWS 1
#define TGON_PLATFORM_FILESYSTEM_UTF16 1
#define TGON_USING_LITTLE_ENDIAN 1
#define TGON_USING_IEEE_754 1
#define TGON_SUPPORT_SSE2 1
#define TGON_SUPPORT_SIMD TGON_SUPPORT_SSE2
#define TGON_USING_SIMD TGON_SUPPORT_SIMD

#if (WINVER >= _WIN32_WINNT_VISTA)
#   define TGON_SUPPORT_DWMAPI 1
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