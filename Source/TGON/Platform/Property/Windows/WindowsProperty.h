#pragma once
#include <sdkddkver.h>

#define TGON_SUPPORT_SSE 1
#define TGON_SUPPORT_SIMD 1

#if ( WINVER >= _WIN32_WINNT_VISTA ) 
#	define TGON_SUPPORT_DWMAPI 1
#else
#endif
