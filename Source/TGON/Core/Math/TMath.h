/**
 * @filename    TMath.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

#include <cmath>
#include <cstdint>

#include "TVector3.h"
#include "Core/Utility/TTypeTraits.h"

namespace tgon {
namespace math {

constexpr float PI = 3.14159265358f;
constexpr float EPSILON = 0.0001f;
constexpr float Deg2Rad = PI / 180;
constexpr float Rad2Deg = 180 / PI;

template <typename Ty, typename = utility::EnableIfFloatingPoint<Ty>>
inline Ty Round(Ty value) noexcept
{
    return std::round(value);
}

/* @return	The value which fractional parts is discarded */
template <typename Ty, typename = utility::EnableIfFloatingPoint<Ty>>
inline Ty Floor(Ty value) noexcept
{
    return std::floor(value);
}

/* @return	Square root value, 반환타입에 문제있음 */
//template <typename Ty,
//          TGON_ENABLE_IF_FLOATING_POINT(Ty)>
//inline Ty Sqrt(Ty value) noexcept
//{
//    return std::sqrt(value);
//}

/* @return	The maximum value between first and second */
template <class Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Max(Ty first, Ty second) noexcept
{
    return (first >= second) ? first : second;
}

/* @return	The minimum value between first and second */
template <class Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Min(Ty first, Ty second) noexcept
{
    return (first <= second) ? first : second;
}

/* @return	The absolute value of parameter value */
template <class Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Abs(Ty value) noexcept
{
    return (value < static_cast<Ty>(0)) ? -value : value;
}

/* @return  A sign of value as it's owned type. */
template<class Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Sign(Ty value) noexcept
{
    return (value > static_cast<Ty>(0)) ? static_cast<Ty>(1) : (value < static_cast<Ty>(0)) ? static_cast<Ty>(-1) : static_cast<Ty>(0);
}

/* @return	A clamped value between min and max */
template <class Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Clamp(Ty value, Ty min, Ty max) noexcept
{
    return Max(Min(value, max), min);
}

/**
 * @param [in] from     Interpolation start value
 * @param [in] to       Interpolation end value
 * @param [in] t        Elapsed time
 * @return              Interpolated value 
 */
constexpr float Lerp(float from, float to, float t) noexcept
{
    return from + (to - from) * t;
}

inline float Smoothstep(float from, float to, float t) noexcept
{
    t = Clamp((t - from) / (to - from), 0.0f, 1.0f);
	return t * t * (3.0f - (2.0f * t));
}
	
/**
 * @param [in] a/b/c    Interpolate target
 * @param [in] t        Elapsed time
 * @return              Interpolated value
 */
inline const TVector3 Bezier(const TVector3& a, const TVector3& b, const TVector3& c, float t) noexcept
{
	float inverse = 1.0f - t;
	return {(inverse * inverse * a) + (2.0f * t * inverse * b) + (t * t * c)};
}

} /* namespace math */
} /* namespace tgon */