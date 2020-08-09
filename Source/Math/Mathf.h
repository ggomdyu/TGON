#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>

#include "Vector3.h"

namespace tg
{

class Mathf final
{
/**@section Constructor */
public:
    Mathf() = delete;

/**@section Method */
public:
    template <Arithmetic _Value>
    [[nodiscard]] static constexpr _Value Abs(const _Value& value) noexcept;
    [[nodiscard]] static constexpr bool Approximately(float first, float second) noexcept;
    [[nodiscard]] static float Asin(float value) noexcept;
    [[nodiscard]] static float Acos(float value) noexcept;
    [[nodiscard]] static float Atan(float value) noexcept;
    [[nodiscard]] static float Atan2(float y, float x) noexcept;
    [[nodiscard]] static float Sin(float value) noexcept;
    [[nodiscard]] static float Cos(float value) noexcept;
    [[nodiscard]] static float Tan(float value) noexcept;
    [[nodiscard]] static float Sqrt(float value) noexcept;
    template <Integral _Value>
    [[nodiscard]] static constexpr bool IsPowerOfTwo(const _Value& value) noexcept;
    template <Integral _Value>
    [[nodiscard]] static constexpr _Value NextPowerOfTwo(_Value value) noexcept;
    template <Integral _Value>
    [[nodiscard]] static constexpr _Value ClosestPowerOfTwo(_Value value) noexcept;
    template <Arithmetic _Value>
    [[nodiscard]] static constexpr _Value Min(const _Value& first, const _Value& second) noexcept;
    template <Arithmetic _Value, Arithmetic... _Types>
    [[nodiscard]] static constexpr _Value Min(const _Value& first, const _Value& second, const _Types&... args) noexcept;
    template <Arithmetic _Value>
    [[nodiscard]] static constexpr _Value Max(const _Value& first, const _Value& second) noexcept;
    template <Arithmetic _Value, Arithmetic... _Types>
    [[nodiscard]] static constexpr _Value Max(const _Value& first, const _Value& second, const _Types&... args) noexcept;
    [[nodiscard]] static float Pow(float value, float p) noexcept;
    [[nodiscard]] static float Exp(float power) noexcept;
    [[nodiscard]] static float Log(float value) noexcept;
    [[nodiscard]] static float Log(float value, float base) noexcept;
    [[nodiscard]] static float Log10(float value) noexcept;
    [[nodiscard]] static float Ceil(float value) noexcept;
    [[nodiscard]] static float Floor(float value) noexcept;
    [[nodiscard]] static float Round(float value) noexcept;
    [[nodiscard]] static constexpr float Sign(float value) noexcept;
    template <Arithmetic _Value>
    [[nodiscard]] static constexpr _Value Clamp(const _Value& value, const _Value& min, const _Value& max) noexcept;
    [[nodiscard]] static constexpr float Clamp01(float value) noexcept;
    template <typename _Value>
    [[nodiscard]] static constexpr _Value Lerp(const _Value& from, const _Value& to, float time) noexcept;
    template <typename _Value>
    [[nodiscard]] static constexpr _Value LerpUnclamped(const _Value& from, const _Value& to, float time) noexcept;
    [[nodiscard]] static constexpr float SmoothStep(float from, float to, float time) noexcept;

/**@section Variable */
public:
    static constexpr float PI = 3.14159274f;
    static constexpr float Infinity = std::numeric_limits<float>::infinity();
    static constexpr float NegativeInfinity = -Infinity;
    static constexpr float Deg2Rad = PI / 180.0f;
    static constexpr float Rad2Deg = 180.0f / PI;
    static constexpr float Epsilon = std::numeric_limits<float>::epsilon();
};

template <Arithmetic _Value>
constexpr _Value Mathf::Abs(const _Value& value) noexcept
{
    return value < 0 ? -value : value;
}

constexpr bool Mathf::Approximately(float first, float second) noexcept
{
    return Abs(second - first) < Max(1E-06f * Max(Abs(first), Abs(second)), Epsilon * 8.0f);
}

inline float Mathf::Asin(float value) noexcept
{
    return std::asin(value);
}

inline float Mathf::Acos(float value) noexcept
{
    return std::acos(value);
}

inline float Mathf::Atan(float value) noexcept
{
    return std::atan(value);
}

inline float Mathf::Atan2(float y, float x) noexcept
{
    return std::atan2(y, x);
}

inline float Mathf::Sin(float value) noexcept
{
    return std::sin(value);
}

inline float Mathf::Cos(float value) noexcept
{
    return std::cos(value);
}

inline float Mathf::Tan(float value) noexcept
{
    return std::tan(value);
}

inline float Mathf::Sqrt(float value) noexcept
{
    return std::sqrt(value);
}

template <Integral _Value>
constexpr bool Mathf::IsPowerOfTwo(const _Value& value) noexcept
{
    return value > 0 && !(value & (value - 1));
}

template <Integral _Value>
constexpr _Value Mathf::NextPowerOfTwo(_Value value) noexcept
{
    --value;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return ++value;
}

template <Integral _Value>
constexpr _Value Mathf::ClosestPowerOfTwo(_Value value) noexcept
{
    const auto nextPowOf2 = NextPowerOfTwo(value);
    const auto prevPowOf2 = nextPowOf2 / 2;
    return Abs(value - nextPowOf2) > Abs(value - prevPowOf2) ? prevPowOf2 : nextPowOf2;
}

template <Arithmetic _Value>
constexpr _Value Mathf::Min(const _Value& first, const _Value& second) noexcept
{
    return first < second ? first : second;
}

template <Arithmetic _Value, Arithmetic... _Types>
constexpr _Value Mathf::Min(const _Value& first, const _Value& second, const _Types&... args) noexcept
{
    return (first <= second) ? Min(first, args...) : Min(second, args...);
}

template <Arithmetic _Value>
constexpr _Value Mathf::Max(const _Value& first, const _Value& second) noexcept
{
    return first > second ? first : second;
}

template <Arithmetic _Value, Arithmetic... _Types>
constexpr _Value Mathf::Max(const _Value& first, const _Value& second, const _Types&... args) noexcept
{
    return (first >= second) ? Max(first, args...) : Max(second, args...);
}

inline float Mathf::Pow(float value, float p) noexcept
{
    return std::pow(value, p);
}

inline float Mathf::Exp(float power) noexcept
{
    return std::exp(power);
}

inline float Mathf::Log(float value) noexcept
{
    return std::log(value);
}

inline float Mathf::Log(float value, float base) noexcept
{
    return Log(value) / Log(base);
}

inline float Mathf::Log10(float value) noexcept
{
    return std::log10(value);
}

inline float Mathf::Ceil(float value) noexcept
{
    return std::ceil(value);
}

inline float Mathf::Floor(float value) noexcept
{
    return std::floor(value);
}

inline float Mathf::Round(float value) noexcept
{
    return std::round(value);
}

template <Arithmetic _Value>
constexpr _Value Mathf::Clamp(const _Value& value, const _Value& min, const _Value& max) noexcept
{
    return std::clamp(value, min, max);
}

constexpr float Mathf::Clamp01(float value) noexcept
{
    return Clamp(value, 0.0f, 1.0f);
}

template <typename _Value>
constexpr _Value Mathf::Lerp(const _Value& from, const _Value& to, float time) noexcept
{
    return from + ((to - from) * std::clamp(time, 0.0f, 1.0f));
}

template <typename _Value>
constexpr _Value Mathf::LerpUnclamped(const _Value& from, const _Value& to, float time) noexcept
{
    return from + ((to - from) * time);
}

constexpr float Mathf::Sign(float value) noexcept
{
    return (value > 0.0f) ? 1.0f : value < 0.0f ? -1.0f : 0.0f;
}

constexpr float Mathf::SmoothStep(float from, float to, float time) noexcept
{
    const auto t = Clamp((time - from) / (to - from), 0.0f, 1.0f);
    return t * t * (3.0f - (2.0f * t));
}

}
