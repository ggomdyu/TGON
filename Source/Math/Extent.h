#pragma once

#include <type_traits>
#include <cstdint>
#include <string>
#include <span>
#include <fmt/format.h>

#include "Core/ExpressionTemplate.h"

namespace tg
{

template <typename _Value> requires IsArithmetic<_Value>
struct BasicExtent2D
{
/**@section Type */
public:
    using ValueType = _Value;

/**@section Constructor */
public:
    constexpr BasicExtent2D() noexcept = default;
    constexpr BasicExtent2D(const _Value& width, const _Value& height) noexcept;
    template <typename _Value2>
    constexpr BasicExtent2D(const BasicExtent2D<_Value2>& extent) noexcept;
    template <typename _ExpressionTemplate> requires IsExpressionTemplate<_ExpressionTemplate>
    constexpr BasicExtent2D(const _ExpressionTemplate& expression);

/**@section Operator */
public:
    constexpr ExpressionTemplate<Plus, BasicExtent2D, BasicExtent2D> operator+(const BasicExtent2D& rhs) const noexcept;
    constexpr ExpressionTemplate<Minus, BasicExtent2D, BasicExtent2D> operator-(const BasicExtent2D& rhs) const noexcept;
    constexpr BasicExtent2D operator*(const _Value& rhs) const noexcept;
    constexpr BasicExtent2D operator/(const _Value& rhs) const;
    constexpr BasicExtent2D operator-() const noexcept;
    BasicExtent2D& operator+=(const BasicExtent2D& rhs) noexcept;
    BasicExtent2D& operator-=(const BasicExtent2D& rhs) noexcept;
    BasicExtent2D& operator*=(const _Value& rhs) noexcept;
    BasicExtent2D& operator/=(const _Value& rhs);
    template <typename _Value2>
    BasicExtent2D& operator=(const BasicExtent2D<_Value2>& rhs) noexcept;
    constexpr bool operator==(const BasicExtent2D& rhs) const noexcept;
    constexpr bool operator!=(const BasicExtent2D& rhs) const noexcept;

/**@section Method */
public:
    int32_t ToString(const std::span<char8_t>& destStr) const;
    int32_t ToString(char8_t* destStr, size_t destStrBufferLen) const;
    [[nodiscard]] std::u8string ToString() const;

/**@section Variable */
public:
    _Value width{}, height{};
};

using FExtent2D = BasicExtent2D<float>;
using DExtent2D = BasicExtent2D<double>;
using I32Extent2D = BasicExtent2D<int32_t>;
using I64Extent2D = BasicExtent2D<int64_t>;
using IExtent2D = BasicExtent2D<int>;
using LLExtent2D = BasicExtent2D<long long>;

template <typename... _Args>
BasicExtent2D(_Args...) -> BasicExtent2D<std::common_type_t<_Args...>>;

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicExtent2D<_Value>::BasicExtent2D(const _Value& width, const _Value& height) noexcept :
    width(width),
    height(height)
{
}

template <typename _Value> requires IsArithmetic<_Value>
template <typename _Value2>
constexpr BasicExtent2D<_Value>::BasicExtent2D(const BasicExtent2D<_Value2>& extent) noexcept :
    width(static_cast<_Value>(extent.width)),
    height(static_cast<_Value>(extent.height))
{
}

template <typename _Value> requires IsArithmetic<_Value>
template <typename _ExpressionTemplate> requires IsExpressionTemplate<_ExpressionTemplate>
constexpr BasicExtent2D<_Value>::BasicExtent2D(const _ExpressionTemplate& expression) :
    BasicExtent2D(expression[0], expression[1])
{
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr ExpressionTemplate<Plus, BasicExtent2D<_Value>, BasicExtent2D<_Value>> BasicExtent2D<_Value>::operator+(const BasicExtent2D& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr ExpressionTemplate<Minus, BasicExtent2D<_Value>, BasicExtent2D<_Value>> BasicExtent2D<_Value>::operator-(const BasicExtent2D& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicExtent2D<_Value> BasicExtent2D<_Value>::operator*(const _Value& rhs) const noexcept
{
    return BasicExtent2D(*this) *= rhs;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicExtent2D<_Value> BasicExtent2D<_Value>::operator/(const _Value& rhs) const
{
    return BasicExtent2D(*this) /= rhs;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicExtent2D<_Value> BasicExtent2D<_Value>::operator-() const noexcept
{
	return BasicExtent2D(-width, -height);
}

template <typename _Value> requires IsArithmetic<_Value>
BasicExtent2D<_Value>& BasicExtent2D<_Value>::operator+=(const BasicExtent2D& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicExtent2D<_Value>& BasicExtent2D<_Value>::operator-=(const BasicExtent2D& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicExtent2D<_Value>& BasicExtent2D<_Value>::operator*=(const _Value& rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicExtent2D<_Value>& BasicExtent2D<_Value>::operator/=(const _Value& rhs)
{
    width /= rhs;
    height /= rhs;

	return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
template <typename _Value2>
BasicExtent2D<_Value>& BasicExtent2D<_Value>::operator=(const BasicExtent2D<_Value2>& rhs) noexcept
{
    width = rhs.width;
    height = rhs.height;

    return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr bool BasicExtent2D<_Value>::operator==(const BasicExtent2D& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr bool BasicExtent2D<_Value>::operator!=(const BasicExtent2D& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _Value> requires IsArithmetic<_Value>
int32_t BasicExtent2D<_Value>::ToString(const std::span<char8_t>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <typename _Value> requires IsArithmetic<_Value>
std::u8string BasicExtent2D<_Value>::ToString() const
{
    std::array<char8_t, 1024> str;
    const int32_t strLen = this->ToString(str);

    return {&str[0], static_cast<size_t>(strLen)};
}

template <typename _Value> requires IsArithmetic<_Value>
int32_t BasicExtent2D<_Value>::ToString(char8_t* destStr, size_t destStrBufferLen) const
{
    auto destStrLen = fmt::format_to_n(destStr, sizeof(destStr[0]) * (destStrBufferLen - 1), u8"{} {}", width, height).size;
    destStr[destStrLen] = u8'\0';

    return static_cast<int32_t>(destStrLen);
}

}