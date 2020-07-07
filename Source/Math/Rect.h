#pragma once

#include <type_traits>
#include <cstdint>
#include <string>
#include <span>
#include <fmt/format.h>

#include "Core/Concepts.h"

namespace tg
{

template <Arithmetic _Value>
struct BasicRect
{
/**@section Type */
public:
    using ValueType = _Value;

/**@section Constructor */
public:
    constexpr BasicRect() noexcept = default;
    constexpr BasicRect(const _Value& x, const _Value& y, const _Value& width, const _Value& height) noexcept;
    template <Arithmetic _Value2>
    constexpr BasicRect(const BasicRect<_Value2>& rhs) noexcept;

/**@section Operator */
public:
    constexpr BasicRect operator-() const noexcept;
    template <Arithmetic _Value2>
    BasicRect& operator=(const BasicRect<_Value2>& rhs) noexcept;
    constexpr bool operator==(const BasicRect& rhs) const noexcept;
    constexpr bool operator!=(const BasicRect& rhs) const noexcept;

/**@section Method */
public:
    [[nodiscard]] constexpr bool Intersect(const BasicRect& rhs) const noexcept;
    int32_t ToString(const std::span<char8_t>& destStr) const;
    int32_t ToString(char8_t* destStr, size_t destStrBufferLen) const;
    [[nodiscard]] std::u8string ToString() const;

/**@section Variable */
public:
    _Value x{}, y{}, width{}, height{};
};

using FRect = BasicRect<float>;
using DRect = BasicRect<double>;
using I32Rect = BasicRect<int32_t>;
using I64Rect = BasicRect<int64_t>;
using IRect = BasicRect<int>;
using LLRect = BasicRect<long long>;

template <Arithmetic... _Args>
BasicRect(_Args...) -> BasicRect<std::common_type_t<_Args...>>;

template <Arithmetic _Value>
constexpr BasicRect<_Value>::BasicRect(const _Value& x, const _Value& y, const _Value& width, const _Value& height) noexcept :
    x(x),
    y(y),
    width(width),
    height(height)
{
}

template <Arithmetic _Value>
template <Arithmetic _Value2>
constexpr BasicRect<_Value>::BasicRect(const BasicRect<_Value2>& rhs) noexcept :
    x(static_cast<_Value>(rhs.x)),
    y(static_cast<_Value>(rhs.y)),
    width(static_cast<_Value>(rhs.width)),
    height(static_cast<_Value>(rhs.height))
{
}

template <Arithmetic _Value>
constexpr BasicRect<_Value> BasicRect<_Value>::operator-() const noexcept
{
    return BasicRect(-x, -y, -width, -height);
}

template <Arithmetic _Value>
template <Arithmetic _Value2>
BasicRect<_Value>& BasicRect<_Value>::operator=(const BasicRect<_Value2>& rhs) noexcept
{
    x = static_cast<_Value>(rhs.x);
    y = static_cast<_Value>(rhs.y);
    width = static_cast<_Value>(rhs.width);
    height = static_cast<_Value>(rhs.height);
    
    return *this;
}

template <Arithmetic _Value>
constexpr bool BasicRect<_Value>::operator==(const BasicRect& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height);
}

template <Arithmetic _Value>
constexpr bool BasicRect<_Value>::operator!=(const BasicRect& rhs) const noexcept
{
    return !(*this == rhs);
}

template <Arithmetic _Value>
constexpr bool BasicRect<_Value>::Intersect(const BasicRect& rhs) const noexcept
{
    return (x <= rhs.width && y <= rhs.height && width >= rhs.x && height >= rhs.y);
}

template <Arithmetic _Value>
int32_t BasicRect<_Value>::ToString(const std::span<char8_t>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <Arithmetic _Value>
std::u8string BasicRect<_Value>::ToString() const
{
    std::array<char8_t, 1024> str{};
    const int32_t strLen = this->ToString(str);

    return {&str[0], static_cast<size_t>(strLen)};
}

template <Arithmetic _Value>
int32_t BasicRect<_Value>::ToString(char8_t* destStr, size_t destStrBufferLen) const
{
    const auto destStrLen = fmt::format_to_n(destStr, sizeof(destStr[0]) * (destStrBufferLen - 1), u8"{} {} {} {}", x, y, width, height).size;
    destStr[destStrLen] = u8'\0';

    return static_cast<int32_t>(destStrLen);
}

}