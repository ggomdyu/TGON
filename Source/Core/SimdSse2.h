#pragma once
#include <cstdint>
#include <emmintrin.h>

#include "Concepts.h"

namespace tg
{

using SimdRegister = __m128;
using DSimdRegister = __m128d;
using I32SimdRegister = __m128i;

#define LoadSimdRegister(f) _mm_loadu_ps(f)
#define StoreSimdRegister(f, r) _mm_storeu_ps(f, r)
#define AddSimdRegister(r1, r2) _mm_add_ps(r1, r2)
#define SubtractSimdRegister(r1, r2) _mm_sub_ps(r1, r2)
#define MultiplySimdRegister(r1, r2) _mm_mul_ps(r1, r2)
#define ShuffleSimdRegister(r1, r2, shuffleMask) _mm_shuffle_ps(r1, r2, shuffleMask)
#define ShuffleMask(a, b, c, d) ((a) | ((b) << 2) | ((c) << 4) | ((d) << 6))

//inline SimdRegister LoadSimdRegister(const float* f)
//{
//    return _mm_loadu_ps(f);
//}
//
//inline SimdRegister LoadSimdRegister(const float(&f)[4])
//{
//    return _mm_loadu_ps(f);
//}
//
//inline void StoreSimdRegister(float* f, SimdRegister r)
//{
//    return _mm_storeu_ps(f, r);
//}
//
//inline SimdRegister AddSimdRegister(SimdRegister r1, SimdRegister r2)
//{
//    return _mm_add_ps(r1, r2);
//}
//
//inline SimdRegister SubSimdRegister(SimdRegister r1, SimdRegister r2)
//{
//    return _mm_sub_ps(r1, r2);
//}
//
//inline SimdRegister MulSimdRegister(SimdRegister r1, SimdRegister r2)
//{
//    return _mm_mul_ps(r1, r2);
//}


}
