#pragma once
#include <sdkddkver.h>

#define TGON_SUPPORT_SSE2
#define TGON_SUPPORT_SIMD

// Windows Vista or better
#if ( WINVER >= _WIN32_WINNT_VISTA )
	#define TGON_SUPPORT_DWMAPI
	#define TGON_SUPPORT_SHL
#endif
