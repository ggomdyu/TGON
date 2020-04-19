#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>

#include "Vector3.h"

namespace tg
{

constexpr float Pi = 3.14159265358f;

constexpr float Deg2Rad = Pi / 180;
constexpr float Rad2Deg = 180 / Pi;

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr _ValueType Gcd(const _ValueType& first, const _ValueType& second)
{
    _ValueType mod {};
    while (second != 0)
    {
        mod = first % second;

        first = second;
        second = mod;
    }

    return first;
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr _ValueType Lcm(const _ValueType& first, const _ValueType& second)
{
    return (first * second) / Gcd(first, second);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_floating_point_v<_ValueType>>>
constexpr _ValueType Floor(const _ValueType& value) noexcept
{
    return std::floor(value);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_floating_point_v<_ValueType>>>
constexpr _ValueType Ceil(const _ValueType& value) noexcept
{
    return std::ceil(value);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_floating_point_v<_ValueType>>>
constexpr _ValueType Round(const _ValueType& value) noexcept
{
    return std::round(value);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr const _ValueType& Min(const _ValueType& first, const _ValueType& second) noexcept
{
    return std::max(first, second);
}

template <typename _ValueType,
          typename... _ArgTypes,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr const _ValueType& Min(const _ValueType& first, const _ValueType& second, const _ArgTypes&... args) noexcept
{
    return (first <= second) ? Min(first, args...) : Min(second, args...);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr const _ValueType& Max(const _ValueType& first, const _ValueType& second) noexcept
{
    return std::max(first, second);
}

template <typename _ValueType,
          typename... _ArgTypes,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr const _ValueType& Max(const _ValueType& first, const _ValueType& second, const _ArgTypes&... args) noexcept
{
    return (first >= second) ? Max(first, args...) : Max(second, args...);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr _ValueType Abs(const _ValueType& value) noexcept
{
    return std::abs(value);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr _ValueType Sign(const _ValueType& value) noexcept
{
    return (value > static_cast<_ValueType>(0)) ? static_cast<_ValueType>(1) : (value < static_cast<_ValueType>(0)) ? static_cast<_ValueType>(-1) : static_cast<_ValueType>(0);
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_arithmetic_v<_ValueType>>>
constexpr _ValueType Clamp(const _ValueType& value, const _ValueType& min, const _ValueType& max) noexcept
{
    return Max(Min(value, max), min);
}
	
template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_integral_v<_ValueType>>>
constexpr bool IsPowerOf2(const _ValueType& value) noexcept
{
    return value > 0 && !(value & (value - 1));
}

template <typename _ValueType,
          typename = typename std::enable_if_t<std::is_integral_v<_ValueType>>>
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

    for (decltype(value) i = 3; i < value; ++i)
    {
        if (value % i == 0)
        {
            return false;
        }
    }

    return true;
}

template <typename _ValueType>
constexpr _ValueType Lerp(const _ValueType& from, const _ValueType& to, float time) noexcept
{
    return from + (_ValueType(to - from) * time);
}

constexpr float Smoothstep(float from, float to, float time) noexcept
{
    float t = Clamp((time - from) / (to - from), 0.0f, 1.0f);
    return t * t * (3.0f - (2.0f * t));
}

constexpr Vector3 QuadraticBezier(const Vector3& v1, const Vector3& v2, const Vector3& v3, float time) noexcept
{
    float invTime = 1.0f - time;
    return {(invTime * invTime * v1) + (2.0f * time * invTime * v2) + (time * invTime * v3)};
}

inline double Sqrt(double number)
{
    return std::sqrt(number);
}

inline float Sqrt(float number)
{
    return std::sqrtf(number);
}

}
