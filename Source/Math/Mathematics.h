#pragma once

#include <algorithm>
#include <cmath>

#include "Core/Concepts.h"

#include "Vector3.h"

namespace tg
{

constexpr float Pi = 3.14159265358f;
constexpr float Deg2Rad = Pi / 180;
constexpr float Rad2Deg = 180 / Pi;

template <Arithmetic _Value>
constexpr _Value Gcd(const _Value& first, const _Value& second)
{
    _Value mod {};
    while (second != 0)
    {
        mod = first % second;

        first = second;
        second = mod;
    }

    return first;
}

template <Arithmetic _Value>
constexpr _Value Lcm(const _Value& first, const _Value& second)
{
    return (first * second) / Gcd(first, second);
}

template <FloatingPoint _Value>
constexpr _Value Floor(const _Value& value) noexcept
{
    return std::floor(value);
}

template <FloatingPoint _Value>
constexpr _Value Ceil(const _Value& value) noexcept
{
    return std::ceil(value);
}

template <FloatingPoint _Value>
constexpr _Value Round(const _Value& value) noexcept
{
    return std::round(value);
}

template <Arithmetic _Value>
constexpr const _Value& Min(const _Value& first, const _Value& second) noexcept
{
    return std::max(first, second);
}

template <Arithmetic _Value, Arithmetic... _ArgTypes>
constexpr const _Value& Min(const _Value& first, const _Value& second, const _ArgTypes&... args) noexcept
{
    return (first <= second) ? Min(first, args...) : Min(second, args...);
}

template <Arithmetic _Value>
constexpr const _Value& Max(const _Value& first, const _Value& second) noexcept
{
    return std::max(first, second);
}

template <Arithmetic _Value, Arithmetic... _ArgTypes>
constexpr const _Value& Max(const _Value& first, const _Value& second, const _ArgTypes&... args) noexcept
{
    return (first >= second) ? Max(first, args...) : Max(second, args...);
}

template <Arithmetic _Value>
constexpr _Value Abs(const _Value& value) noexcept
{
    return std::abs(value);
}

template <Arithmetic _Value>
constexpr _Value Sign(const _Value& value) noexcept
{
    return (value > static_cast<_Value>(0)) ? static_cast<_Value>(1) : (value < static_cast<_Value>(0)) ? static_cast<_Value>(-1) : static_cast<_Value>(0);
}

template <Arithmetic _Value>
constexpr _Value Clamp(const _Value& value, const _Value& min, const _Value& max) noexcept
{
    return Max(Min(value, max), min);
}
	
template <Integral _Value>
constexpr bool IsPowerOf2(const _Value& value) noexcept
{
    return value > 0 && !(value & (value - 1));
}

template <Integral _Value>
constexpr bool IsPrimeNumber(const _Value& value) noexcept
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

template <typename _Value>
constexpr _Value Lerp(const _Value& from, const _Value& to, float time) noexcept
{
    return from + ((to - from) * std::clamp(time, 0.0f, 1.0f));
}

template <typename _Value>
constexpr _Value LerpUnclamped(const _Value& from, const _Value& to, float time) noexcept
{
    return from + ((to - from) * time);
}

constexpr float Smoothstep(float from, float to, float time) noexcept
{
    const float t = Clamp((time - from) / (to - from), 0.0f, 1.0f);
    return t * t * (3.0f - (2.0f * t));
}

constexpr Vector3 QuadraticBezier(const Vector3& v1, const Vector3& v2, const Vector3& v3, float time) noexcept
{
    const float invTime = 1.0f - time;
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
