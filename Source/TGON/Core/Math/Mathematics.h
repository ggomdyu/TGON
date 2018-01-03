/**
 * @filename    Mathematics.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Vector3.h"

#include <cmath>
#include <type_traits>
#include <cstdint>

namespace tgon
{
namespace math
{

constexpr const float Pi = 3.14159265358f;

constexpr const float Deg2Rad = Pi / 180;
constexpr const float Rad2Deg = 180 / Pi;

/**
 * @brief   Returns the greatest common divisor using Euclidean algorithm.
 @ @see     https://en.wikipedia.org/wiki/Euclidean_algorithm
 */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr const _ValueType Gcd(_ValueType first, _ValueType second)
{
    _ValueType mod;
    while (second != 0)
    {
        mod = first % second;

        first = second;
        second = mod;
    }

    return first;
}

/* @brief   Returns the least common multiple. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr const _ValueType Lcm(const _ValueType& first, const _ValueType& second)
{
    return (first * second) / Gcd(first, second);
}

/* @brief   Discards fractional part of floating point value. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type>
constexpr const _ValueType Floor(const _ValueType& value) noexcept
{
    using IntergerType = typename std::conditional<sizeof(_ValueType) == sizeof(int8_t), int8_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int16_t), int16_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int32_t), int32_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int64_t), int64_t, void>::type>::type>::type>::type;

    IntergerType flooredValue = static_cast<IntergerType>(value);
    return value < flooredValue ? flooredValue - static_cast<_ValueType>(1.0) : flooredValue;
}

template <typename _ValueType,
          typename = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type>
constexpr _ValueType Ceil(const _ValueType& value) noexcept
{
    using IntergerType = typename std::conditional<sizeof(_ValueType) == sizeof(int8_t), int8_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int16_t), int16_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int32_t), int32_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int64_t), int64_t, void>::type>::type>::type>::type;

    IntergerType flooredValue = static_cast<IntergerType>(value);
    return value > flooredValue ? flooredValue + static_cast<_ValueType>(1.0) : flooredValue;
}

/* @brief   Round off the given floating point value. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type>
constexpr const _ValueType Round(_ValueType value) noexcept
{
    using IntergerType = typename std::conditional<sizeof(_ValueType) == sizeof(int8_t), int8_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int16_t), int16_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int32_t), int32_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int64_t), int64_t, void>::type>::type>::type>::type;

    return static_cast<_ValueType>(static_cast<IntergerType>(value + ((value >= static_cast<_ValueType>(0.0)) ? static_cast<_ValueType>(0.5) : static_cast<_ValueType>(-0.5))));
}

/* @return	Returns largest value of the given parameters. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Min(const _ValueType& first, const _ValueType& second) noexcept
{
    return (first <= second) ? first : second;
}

template <typename _ValueType,
          typename ..._ArgTypes,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Min(const _ValueType& first, const _ValueType& second, const _ArgTypes&... args) noexcept
{
    return (first <= second) ? Min(first, args...) : Min(second, args...);
}

template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Max(const _ValueType& first, const _ValueType& second) noexcept
{
    return (first >= second) ? first : second;
}

template <typename _ValueType,
          typename ..._ArgTypes,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Max(const _ValueType& first, const _ValueType& second, const _ArgTypes&... args) noexcept
{
    return (first >= second) ? Max(first, args...) : Max(second, args...);
}

/* @brief   Get the absolute value. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Abs(const _ValueType& value) noexcept
{
    return (value < static_cast<_ValueType>(0)) ? -value : value;
}

/* @brief  Get the sign of value represented as 1, -1 or 0 */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Sign(const _ValueType& value) noexcept
{
    return (value > static_cast<_ValueType>(0)) ? static_cast<_ValueType>(1) : (value < static_cast<_ValueType>(0)) ? static_cast<_ValueType>(-1) : static_cast<_ValueType>(0);
}

/* @return	Returns clamped value to min and max range */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Clamp(const _ValueType& value, const _ValueType& min, const _ValueType& max) noexcept
{
    return Max(Min(value, max), min);
}
	
template <typename _ValueType,
          typename = typename std::enable_if<std::is_integral<_ValueType>::value>::type>
constexpr bool IsPowerOf2(const _ValueType& value) noexcept
{
    return value > 0 && !(value & (value - 1));
}

template <typename _ValueType,
          typename = typename std::enable_if<std::is_integral<_ValueType>::value>::type>
constexpr bool IsPrimeNumber(const _ValueType& value) noexcept
{
    if (value <= 1)
    {
        return false;
    }

    if (value % 2 == 0)
    {
        return (value == 2);
    }

    for (int i = 3; i < value; ++i)
    {
        if (value % i == 0)
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief               Performs Linear interpolation.
 * @param [in] from     Interpolation start value
 * @param [in] to       Interpolation end value
 * @param [in] time     Elapsed time ratio between 0.0 ~ 1.0
 * @return              Returns Interpolated value
 */
template <typename _ValueType>
constexpr const _ValueType Lerp(const _ValueType& from, const _ValueType& to, float time) noexcept
{
    return from + ((to - from) * time);
}

constexpr float Smoothstep(float from, float to, float time) noexcept
{
    float t = Clamp((time - from) / (to - from), 0.0f, 1.0f);
    return t * t * (3.0f - (2.0f * t));
}

/**
 * @brief               Calculates Two-dimensional bezier curve.
 * @param [in] a        The first vertex
 * @param [in] b        The second vertex
 * @param [in] c        The third vertex
 * @param [in] time     Elapsed time ratio between 0.0 ~ 1.0
 * @return              Returns Interpolated vertex.
 */
constexpr const Vector3 QuadraticBezier(const Vector3& v1, const Vector3& v2, const Vector3& v3, float time) noexcept
{
	float invTime = 1.0f - time;
	return {};//{(invTime * invTime * v1) + (2.0f * time * invTime * v2) + (time * invTime * v3)};
}

//float Sqrt()
//{
//    _mm_set_ps1(0.0f);
//    return 0.0f;
////#ifdef TGON_SUPPORT_SSE
////    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ps1(0.0f)));
////#endif
//}

} /* namespace math */
} /* namespace tgon */
