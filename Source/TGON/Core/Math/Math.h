/**
 * @filename    Math.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cmath>
#include <type_traits>
#include <cstdint>

#include "Vector3.h"

namespace tgon
{
namespace math
{

constexpr float PI = 3.14159265358f;
constexpr float EPSILON = 0.0001f;
constexpr float Deg2Rad = PI / 180;
constexpr float Rad2Deg = 180 / PI;

template <typename _ValueType,
          typename = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type>
inline _ValueType Round(const _ValueType& value) noexcept
{
    return round(value);
}

/* @return	Value which fractional part is discarded */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type>
constexpr _ValueType Floor(const _ValueType& value) noexcept
{
    using IntergerType = typename std::conditional<sizeof(_ValueType) == sizeof(int8_t), int8_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int16_t), int16_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int32_t), int32_t,
                         typename std::conditional<sizeof(_ValueType) == sizeof(int64_t), int64_t, void>::type>::type>::type>::type;

    return ((_ValueType)((IntergerType)value));;
}

/* @return	Returns Square root value. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
inline _ValueType Sqrt(const _ValueType& value) noexcept
{
    return sqrt(value);
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
    using tgon::math::Min;
    return (first <= second) ? Min(first, args...) : Min(second, args...);
}

/* @return	Returns largest value of the given parameters. */
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
    using tgon::math::Max;
    return (first >= second) ? Max(first, args...) : Max(second, args...);
}

/* @return	Returns the absolute value. */
template <typename _ValueType,
          typename = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type>
constexpr _ValueType Abs(const _ValueType& value) noexcept
{
    return (value < static_cast<_ValueType>(0)) ? -value : value;
}

/* @return  Returns the sign of value which represented as 1, -1 or 0 */
template<typename _ValueType,
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

/**
 * @brief                   Perform Linear interpolation.
 * @param [in] from         Interpolation start value
 * @param [in] to           Interpolation end value
 * @param [in] timeRatio    Elapsed time ratio between 0.0 ~ 1.0
 * @return                  Returns Interpolated value
 */
constexpr const Vector3 Lerp(const Vector3& from, const Vector3& to, float timeRatio) noexcept
{
    return from + ((from - to) * timeRatio);
}

constexpr float Lerp(float from, float to, float timeRatio) noexcept
{
    return from + ((to - from) * timeRatio);
}

#if (__cplusplus == 201402L)
constexpr
#elif (__cplusplus == 201103L)
inline
#endif
float Smoothstep(float from, float to, float timeRatio) noexcept
{
    timeRatio = Clamp((timeRatio - from) / (to - from), 0.0f, 1.0f);
	return timeRatio * timeRatio * (3.0f - (2.0f * timeRatio));
}

//#if (__cplusplus == 201402L)
//constexpr
//#elif (__cplusplus == 201103L)
//inline
//#endif
/**
 * @brief                   Two-dimensional bezier curve
 * @param [in] a            The first vertex
 * @param [in] b            The second vertex
 * @param [in] c            The third vertex
 * @param [in] timeRatio    Elapsed time ratio between 0.0 ~ 1.0
 * @return                  Returns Interpolated vertex.
 */
//const Vector3 QuadraticBezier(const Vector3& a, const Vector3& b, const Vector3& c, float timeRatio) noexcept
//{
//	float inversedTime = 1.0f - timeRatio;
//	return {(inversedTime * inversedTime * a) + (2.0f * timeRatio * inversedTime * b) + (timeRatio * inversedTime * c)};
//}

} /* namespace math */
} /* namespace tgon */
