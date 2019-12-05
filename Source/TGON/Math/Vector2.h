/**
 * @file    Vector2.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <string>
#include <gsl/span>

#include "Misc/ExpressionTemplate.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF sprintf
#endif

namespace tgon
{
    
template <typename _ValueType>
struct BasicVector2
{
/**@section Constructor */
public:
    constexpr BasicVector2() noexcept = default;
    constexpr BasicVector2(const _ValueType& scalar) noexcept;
    constexpr BasicVector2(const _ValueType& x, const _ValueType& y) noexcept;
    template <typename _DerivedExpressionType>
    constexpr BasicVector2(const BaseExpression<_DerivedExpressionType>& expression);

/**@section Operator */
public:
    constexpr const AddExpression<BasicVector2, BasicVector2> operator+(const BasicVector2& rhs) const noexcept;
    constexpr const SubtractExpression<BasicVector2, BasicVector2> operator-(const BasicVector2& rhs) const noexcept;
    friend constexpr const BasicVector2 operator*(const _ValueType& scalar, const BasicVector2& v) noexcept;
    constexpr const BasicVector2 operator*(const _ValueType& scalar) const noexcept;
    constexpr const BasicVector2 operator-(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator+(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator/(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator-() const noexcept;
    BasicVector2& operator+=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator-=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator*=(const BasicVector2& rhs) noexcept;
    BasicVector2& operator*=(_ValueType scalar) noexcept;
    BasicVector2& operator/=(_ValueType scalar);
    constexpr bool operator==(const BasicVector2& rhs) const noexcept;
    constexpr bool operator!=(const BasicVector2& rhs) const noexcept;
    _ValueType& operator[](std::size_t index) noexcept;
    _ValueType operator[](std::size_t index) const noexcept;
    
/**@section Method */
public:
    static constexpr const BasicVector2 Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept;
    static constexpr _ValueType Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    constexpr _ValueType Dot(const BasicVector2& v) const noexcept;
    static _ValueType Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    static _ValueType Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    _ValueType Distance(const BasicVector2& v) const noexcept;
    _ValueType& At(std::size_t index);
    _ValueType At(std::size_t index) const;
    _ValueType Length() const noexcept;
    _ValueType LengthSq() const noexcept;
    void Normalize();
    const BasicVector2 Normalized() const;
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    std::string ToString() const;

/**@section Variable */
public:
	_ValueType x{}, y{};
};

using I32Vector2 = BasicVector2<int32_t>;
using I64Vector2 = BasicVector2<int64_t>;
using IVector2 = BasicVector2<int>;
using Vector2 = BasicVector2<float>;
using DVector2 = BasicVector2<double>;

template <typename... _Types>
BasicVector2(_Types...) -> BasicVector2<std::common_type_t<_Types...>>;

template <typename _ValueType>
constexpr BasicVector2<_ValueType>::BasicVector2(const _ValueType& scalar) noexcept :
    x(scalar),
    y(scalar)
{
}

template <typename _ValueType>
constexpr BasicVector2<_ValueType>::BasicVector2(const _ValueType& x, const _ValueType& y) noexcept :
    x(x),
    y(y)
{
}

template <typename _ValueType>
template <typename _DerivedExpressionType>
constexpr BasicVector2<_ValueType>::BasicVector2(const BaseExpression<_DerivedExpressionType>& expression) :
    x(expression[0]),
    y(expression[1])
{
}

template <typename _ValueType>
constexpr const AddExpression<BasicVector2<_ValueType>, BasicVector2<_ValueType>> BasicVector2<_ValueType>::operator+(const BasicVector2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const SubtractExpression<BasicVector2<_ValueType>, BasicVector2<_ValueType>> BasicVector2<_ValueType>::operator-(const BasicVector2& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> operator*(const _ValueType& scalar, const BasicVector2<_ValueType>& v) noexcept
{
    return v * scalar;
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::operator*(const _ValueType& scalar) const noexcept
{
    return BasicVector2(x * scalar, y * scalar);
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::operator-(const _ValueType& scalar) const
{
    return BasicVector2(x - scalar, y - scalar);
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::operator+(const _ValueType& scalar) const
{
    return BasicVector2(x + scalar, y + scalar);
}
    
template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::operator/(const _ValueType& scalar) const
{
    return BasicVector2(x / scalar, y / scalar);
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::operator-() const noexcept
{
    return BasicVector2(-x, -y);
}

template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator+=(const BasicVector2& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator-=(const BasicVector2& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;
    
    return *this;
}
    
template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator*=(const BasicVector2& rhs) noexcept
{
    x *= rhs.x;
    y *= rhs.y;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator*=(_ValueType scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator/=(_ValueType scalar)
{
    x /= scalar;
    y /= scalar;
    
    return *this;
}

template <typename _ValueType>
constexpr bool BasicVector2<_ValueType>::operator==(const BasicVector2& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y);
}

template <typename _ValueType>
constexpr bool BasicVector2<_ValueType>::operator!=(const BasicVector2& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _ValueType>
inline _ValueType& BasicVector2<_ValueType>::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
constexpr const BasicVector2<_ValueType> BasicVector2<_ValueType>::Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept
{
    return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
}

template <typename _ValueType>
constexpr _ValueType BasicVector2<_ValueType>::Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return v1.Dot(v2);
}

template <typename _ValueType>
constexpr _ValueType BasicVector2<_ValueType>::Dot(const BasicVector2& v) const noexcept
{
    return (x * v.x) + (y * v.y);
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return std::acos(v1.Dot(v2) / (v1.Length() * v2.Length()));
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept
{
    return BasicVector2(v1 - v2).Length();
}
    
template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::Distance(const BasicVector2& v) const noexcept
{
    return BasicVector2(*this - v).Length();
}

template <typename _ValueType>
inline _ValueType& BasicVector2<_ValueType>::At(std::size_t index)
{
    assert((index < 2 && index > -1) && "BasicVector2 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::At(std::size_t index) const
{
    assert((index < 2 && index > -1) && "BasicVector2 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::Length() const noexcept
{
    return std::sqrtf(this->LengthSq());
}

template <typename _ValueType>
inline _ValueType BasicVector2<_ValueType>::LengthSq() const noexcept
{
    return (x * x) + (y * y);
}

template <typename _ValueType>
inline void BasicVector2<_ValueType>::Normalize()
{
    *this = this->Normalized();
}

template <typename _ValueType>
inline const BasicVector2<_ValueType> BasicVector2<_ValueType>::Normalized() const
{
    _ValueType length = this->Length();
    
    return Vector2(x / length, y / length);
}

template <typename _ValueType>
inline int32_t BasicVector2<_ValueType>::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <typename _ValueType>
inline int32_t BasicVector2<_ValueType>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f", x, y);
}

template <typename _ValueType>
inline std::string BasicVector2<_ValueType>::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

} /* namespace tgon */

#undef TGON_SPRINTF
