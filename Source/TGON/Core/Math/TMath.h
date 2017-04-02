/**
 * filename TMath.h
 * author   ggomdyu
 * since    03/14/2016
 */

#pragma once
#include "../Platform/TConfig.h"
#include "TVector3.h"

#include <cmath>
#include <cstdint>

namespace tgon
{

class TGON_API TMath
{
/** 
 * @section Static variables
 */ 
public:
    static constexpr float PI = 3.14159265358f;
    static constexpr float EPSILON = 0.0001f;
    static constexpr float Deg2Rad = PI / 180;
    static constexpr float Rad2Deg = 180 / PI;

/**
 * @section Commands
 */ 
public:
    template <typename Ty>
	static Ty Round(Ty value) noexcept;

	/* @return	The value which fractional parts is discarded */
    template <typename Ty>
	static Ty Floor(Ty value) noexcept;

	/* @return	Square root value */
    template <typename Ty>
	static Ty Sqrt(Ty value) noexcept;

	/* @return	Maximum value between first and second */
	template <class Ty>
	static constexpr Ty Max(Ty first, Ty second) noexcept;

	/* @return	Minimum value between first and second */
	template <class Ty>
	static constexpr Ty Min(Ty first, Ty second) noexcept;

	/* @return	Absolute value */
	template <class Ty>
	static constexpr Ty Abs(Ty value) noexcept;

	/* @return  The sign of value as it's owned type. */
	template<class Ty>
	static constexpr Ty Sign(Ty value) noexcept;

	/* @return	Clamped value between min and max */
	template <class Ty>
	static constexpr Ty Clamp(Ty value, Ty min, Ty max) noexcept;

	/**
	 * @param	from	Interpolation start value
	 * @param	to		Interpolation end value
	 * @param	t		Elapsed time
	 * @return			Interpolated value 
	 */
	static constexpr float Lerp(float from, float to, float t) noexcept;

	static float Smoothstep(float from, float to, float t) noexcept;
	
	/**
	 * @param	a/b/c	Interpolate target
	 * @param	t		Elapsed time
	 * @return			Interpolated value
	 */
	static const TVector3 Bezier(const TVector3& a, const TVector3& b, const TVector3& c, float t) noexcept;

/** 
 * @section Ctor/Dtor
 */ 
public:
    TMath() = delete;
    ~TMath() = delete;
};

template <typename Ty>
inline Ty TMath::Round(Ty value) noexcept
{
    return std::round(value);
}

template <typename Ty>
inline Ty TMath::Floor(Ty value) noexcept
{
	return std::floor(value);
}

//inline std::size_t Math::FloorToInt(float value)
//{
//#if TGON_SUPPORT_SSE2
//	return ( _mm_cvt_ss2si( _mm_set_ss(value +vvalueal-0.5f )) >> 1 );
//#else
////return static_cast<std::size_t>(std::floor(value));
//#endif
//}

template <class Ty>
inline Ty TMath::Sqrt(Ty value) noexcept
{
	return std::sqrt(value);
}

template <class Ty>
constexpr Ty TMath::Max(Ty first, Ty second) noexcept
{
	return (first >= second) ? first : second;
}

template <class Ty>
constexpr Ty TMath::Min(Ty first, Ty second) noexcept
{
	return (first <= second) ? first : second;
}

template <class Ty>
constexpr Ty TMath::Abs(Ty value) noexcept
{
	return (value < static_cast<Ty>(0)) ? -value : value;
}

template<class Ty>
constexpr Ty TMath::Sign(Ty value) noexcept
{
	return (value > static_cast<Ty>(0)) ? static_cast<Ty>(1) : (value < static_cast<Ty>(0)) ? static_cast<Ty>(-1) : static_cast<Ty>(0);
}

template <class Ty>
constexpr Ty TMath::Clamp(Ty value, Ty min, Ty max) noexcept
{
	return TMath::Max(TMath::Min(value, max), min);
}

constexpr float TMath::Lerp(float from, float to, float t) noexcept
{
	return from + (to - from) * t;
}

inline float TMath::Smoothstep(float from, float to, float t) noexcept
{
	t = TMath::Clamp((t - from) / (to - from), 0.0f, 1.0f);
	return t * t * (3.0f - (2.0f * t));
}

inline const TVector3 TMath::Bezier(const TVector3& a, const TVector3& b, const TVector3& c, float t) noexcept
{
	float inv = 1.0f - t;
	return {(inv * inv * a) + (2.0f * t * inv * b) + (t * t * c)};
}

} /* namespace tgon */