/**
 * @filename    TMath.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cmath>
#include <cstdint>

#include "Core/Platform/Config.h"
#include "Core/Utility/TypeTraits.h"

#include "Vector3.h"

namespace tgon
{
namespace math
{

constexpr float PI = 3.14159265358f;
constexpr float EPSILON = 0.0001f;
constexpr float Deg2Rad = PI / 180;
constexpr float Rad2Deg = 180 / PI;

template <typename Ty, typename = utility::EnableIfFloatingPoint<Ty>>
inline Ty Round(Ty value) noexcept
{
    return std::round(value);
}

/* @return	Value which fractional part is discarded */
template <typename Ty, typename = utility::EnableIfFloatingPoint<Ty>>
inline Ty Floor(Ty value) noexcept
{
    return std::floor(value);
}

/* @return	Square root value, π›»Ø≈∏¿‘ø° πÆ¡¶¿÷¿Ω */
//template <typename Ty,
//          TGON_ENABLE_IF_FLOATING_POINT(Ty)>
//inline Ty Sqrt(Ty value) noexcept
//{
//    return std::sqrt(value);
//}

/* @return	Returns the maximum value of the given parameters. */
template <typename Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Max(Ty first, Ty second) noexcept
{
    return (first >= second) ? first : second;
}

/* @return	Returns the minimum value of the given parameters. */
template <typename Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Min(Ty first, Ty second) noexcept
{
    return (first <= second) ? first : second;
}

/* @return	Returns the absolute value. */
template <typename Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Abs(Ty value) noexcept
{
    return (value < static_cast<Ty>(0)) ? -value : value;
}

/* @return  Returns the sign of value which represented as 1, -1 or 0 */
template<typename Ty, typename = utility::EnableIfArithmetic<Ty>>
constexpr Ty Sign(Ty value) noexcept
{
    return (value > static_cast<Ty>(0)) ? static_cast<Ty>(1) : (value < static_cast<Ty>(0)) ? static_cast<Ty>(-1) : static_cast<Ty>(0);
}

/* @return	Returns clamped value to min and max range */
template <typename Ty, typename = utility::EnableIfArithmetic<Ty>>
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
 * @param [in] a        The first point of Bezier curve
 * @param [in] b        The second point of Bezier curve
 * @param [in] c        The third point of Bezier curve
 * @param [in] t        Elapsed time
 * @return              Interpolated value
 */
inline const Vector3 Bezier(const Vector3& a, const Vector3& b, const Vector3& c, float t) noexcept
{
	float inverse = 1.0f - t;
	return {(inverse * inverse * a) + (2.0f * t * inverse * b) + (t * t * c)};
}

} /* namespace math */
} /* namespace tgon */
