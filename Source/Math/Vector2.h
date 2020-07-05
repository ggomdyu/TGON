#pragma once

#include <cstdint>
#include <cassert>
#include <cmath>
#include <string>
#include <span>
#include <array>
#include <fmt/format.h>

#include "Core/ExpressionTemplate.h"
#include "Core/Concepts.h"

namespace tg
{
    
template <typename _Value> requires IsArithmetic<_Value>
struct BasicVector2
{
/**@section Type */
public:
    using ValueType = _Value;

/**@section Constructor */
public:
    constexpr BasicVector2() noexcept = default;
    constexpr BasicVector2(const _Value& scalar) noexcept;
    constexpr BasicVector2(const _Value& x, const _Value& y) noexcept;
    template <typename _ExpressionTemplate> requires IsExpressionTemplate<_ExpressionTemplate>
    constexpr BasicVector2(const _ExpressionTemplate& expression);

/**@section Operator */
public:
    constexpr ExpressionTemplate<Plus, BasicVector2, BasicVector2> operator+(const BasicVector2& rhs) const noexcept;
    constexpr ExpressionTemplate<Minus, BasicVector2, BasicVector2> operator-(const BasicVector2& rhs) const noexcept;
    constexpr BasicVector2 operator*(const _Value& scalar) const noexcept;
    constexpr BasicVector2 operator/(const _Value& scalar) const;
    friend constexpr BasicVector2 operator*(const _Value& lhs, const BasicVector2<_Value>& rhs) noexcept;
    friend constexpr BasicVector2 operator/(const _Value& lhs, const BasicVector2<_Value>& rhs);
    constexpr BasicVector2 operator-() const noexcept;
    BasicVector2& operator+=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator-=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator*=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator*=(_Value scalar) noexcept;
    BasicVector2& operator/=(_Value scalar);
    constexpr bool operator==(const BasicVector2& rhs) const noexcept;
    constexpr bool operator!=(const BasicVector2& rhs) const noexcept;
    _Value& operator[](int32_t index) noexcept;
    _Value operator[](int32_t index) const noexcept;
    
/**@section Method */
public:
    [[nodiscard]] static constexpr BasicVector2 Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept;
    [[nodiscard]] static constexpr _Value Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    [[nodiscard]] constexpr _Value Dot(const BasicVector2& v) const noexcept;
    [[nodiscard]] static _Value Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    [[nodiscard]] static _Value Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    [[nodiscard]] _Value Distance(const BasicVector2& v) const noexcept;
    [[nodiscard]] _Value& At(int32_t index);
    [[nodiscard]] _Value At(int32_t index) const;
    [[nodiscard]] _Value Length() const noexcept;
    [[nodiscard]] _Value LengthSq() const noexcept;
    void Normalize();
    [[nodiscard]] BasicVector2 Normalized() const;
    int32_t ToString(const std::span<char8_t>& destStr) const;
    int32_t ToString(char8_t* destStr, size_t destStrBufferLen) const;
    [[nodiscard]] std::u8string ToString() const;

/**@section Variable */
public:
	_Value x{}, y{};
};

using I32Vector2 = BasicVector2<int32_t>;
using I64Vector2 = BasicVector2<int64_t>;
using IVector2 = BasicVector2<int>;
using Vector2 = BasicVector2<float>;
using DVector2 = BasicVector2<double>;

template <typename... _Args>
BasicVector2(_Args...) -> BasicVector2<std::common_type_t<_Args...>>;

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value>::BasicVector2(const _Value& scalar) noexcept :
    x(scalar),
    y(scalar)
{
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value>::BasicVector2(const _Value& x, const _Value& y) noexcept :
    x(x),
    y(y)
{
}

template <typename _Value> requires IsArithmetic<_Value>
template <typename _ExpressionTemplate> requires IsExpressionTemplate<_ExpressionTemplate>
constexpr BasicVector2<_Value>::BasicVector2(const _ExpressionTemplate& expression) :
    BasicVector2(expression[0], expression[1])
{
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr ExpressionTemplate<Plus, BasicVector2<_Value>, BasicVector2<_Value>> BasicVector2<_Value>::operator+(const BasicVector2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr ExpressionTemplate<Minus, BasicVector2<_Value>, BasicVector2<_Value>> BasicVector2<_Value>::operator-(const BasicVector2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> BasicVector2<_Value>::operator*(const _Value& scalar) const noexcept
{
    return BasicVector2(x * scalar, y * scalar);
}
    
template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> BasicVector2<_Value>::operator/(const _Value& scalar) const
{
    return BasicVector2(x / scalar, y / scalar);
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> operator*(const _Value& lhs, const BasicVector2<_Value>& rhs) noexcept
{
    return rhs * lhs;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> operator/(const _Value& lhs, const BasicVector2<_Value>& rhs) noexcept
{
    return rhs / lhs;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> BasicVector2<_Value>::operator-() const noexcept
{
    return BasicVector2(-x, -y);
}

template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value>& BasicVector2<_Value>::operator+=(const BasicVector2& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    
    return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value>& BasicVector2<_Value>::operator-=(const BasicVector2& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;
    
    return *this;
}
    
template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value>& BasicVector2<_Value>::operator*=(const BasicVector2& rhs) noexcept
{
    x *= rhs.x;
    y *= rhs.y;
    
    return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value>& BasicVector2<_Value>::operator*=(_Value scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    
    return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value>& BasicVector2<_Value>::operator/=(_Value scalar)
{
    x /= scalar;
    y /= scalar;
    
    return *this;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr bool BasicVector2<_Value>::operator==(const BasicVector2& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y);
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr bool BasicVector2<_Value>::operator!=(const BasicVector2& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _Value> requires IsArithmetic<_Value>
_Value& BasicVector2<_Value>::operator[](int32_t index) noexcept
{
    return *(&x + index);
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::operator[](int32_t index) const noexcept
{
    return *(&x + index);
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr BasicVector2<_Value> BasicVector2<_Value>::Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept
{
    return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr _Value BasicVector2<_Value>::Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return v1.Dot(v2);
}

template <typename _Value> requires IsArithmetic<_Value>
constexpr _Value BasicVector2<_Value>::Dot(const BasicVector2& v) const noexcept
{
    return (x * v.x) + (y * v.y);
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return std::acos(v1.Dot(v2) / (v1.Length() * v2.Length()));
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return BasicVector2(v1 - v2).Length();
}
    
template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::Distance(const BasicVector2& v) const noexcept
{
    return BasicVector2(*this - v).Length();
}

template <typename _Value> requires IsArithmetic<_Value>
_Value& BasicVector2<_Value>::At(int32_t index)
{
    assert(index < 2 && index > -1);
    return *(&x + index);
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::At(int32_t index) const
{
    assert(index < 2 && index > -1);
    return *(&x + index);
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::Length() const noexcept
{
    return std::sqrtf(this->LengthSq());
}

template <typename _Value> requires IsArithmetic<_Value>
_Value BasicVector2<_Value>::LengthSq() const noexcept
{
    return (x * x) + (y * y);
}

template <typename _Value> requires IsArithmetic<_Value>
void BasicVector2<_Value>::Normalize()
{
    _Value length = this->Length();
    
    x = x / length;
    y = y / length;
}

template <typename _Value> requires IsArithmetic<_Value>
BasicVector2<_Value> BasicVector2<_Value>::Normalized() const
{
    _Value length = this->Length();
    return Vector2(x / length, y / length);
}

template <typename _Value> requires IsArithmetic<_Value>
int32_t BasicVector2<_Value>::ToString(const std::span<char8_t>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <typename _Value> requires IsArithmetic<_Value>
std::u8string BasicVector2<_Value>::ToString() const
{
    std::array<char8_t, 1024> str{};
    const int32_t strLen = this->ToString(str);

    return {&str[0], static_cast<size_t>(strLen)};
}

template <typename _Value> requires IsArithmetic<_Value>
int32_t BasicVector2<_Value>::ToString(char8_t* destStr, size_t destStrBufferLen) const
{
    const auto destStrLen = fmt::format_to_n(destStr, sizeof(destStr[0]) * (destStrBufferLen - 1), u8"{} {}", x, y).size;
    destStr[destStrLen] = u8'\0';

    return static_cast<int32_t>(destStrLen);
}

}
