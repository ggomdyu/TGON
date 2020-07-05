#pragma once

#if TGON_SIMD_SSE2
#include "SimdSse2.h"
#elif TGON_SIMD_NEON
#include "SimdNeon.h"
#endif