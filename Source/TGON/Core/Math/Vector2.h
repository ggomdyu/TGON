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

#include "Core/Utility/ExpressionTemplate.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF sprintf
#endif

namespace tgon
{
    
template <typename _ValueType>
struct BasicVector2 final
{
/**@section Constructor */
public:
    /**@brief   Initializes x, y components to 0. */
    constexpr BasicVector2() noexcept;

    /**@brief   Initializes x, y components with the specified value. */
    constexpr BasicVector2(const _ValueType& scalar) noexcept;

    /**@brief   Initializes x, y components with the specified value. */
    constexpr BasicVector2(const _ValueType& x, const _ValueType& y) noexcept;

    /**@brief   Initializes x, y components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr BasicVector2(const BaseExpression<_DerivedExpressionType>& expression);

/**@section Public perator */
public:
    constexpr const AddExpression<BasicVector2, BasicVector2> operator+(const BasicVector2& v) const noexcept;
    constexpr const SubtractExpression<BasicVector2, BasicVector2> operator-(const BasicVector2& v) const noexcept;
    friend constexpr const BasicVector2 operator*(const _ValueType& scalar, const BasicVector2& v) noexcept;
    constexpr const BasicVector2 operator*(const _ValueType& scalar) const noexcept;
    constexpr const BasicVector2 operator-(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator+(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator/(const _ValueType& scalar) const;
    constexpr const BasicVector2 operator-() const noexcept;
    BasicVector2& operator+=(const BasicVector2& v) noexcept;
    BasicVector2& operator-=(const BasicVector2& v) noexcept;
    BasicVector2& operator*=(const BasicVector2& v) noexcept;
    BasicVector2& operator*=(_ValueType scalar) noexcept;
    BasicVector2& operator/=(_ValueType scalar);
    constexpr bool operator==(const BasicVector2& v) const noexcept;
    constexpr bool operator!=(const BasicVector2& v) const noexcept;
    _ValueType& operator[](std::size_t index) noexcept;
    const _ValueType& operator[](std::size_t index) const noexcept;
    
/**@section Method */
public:
    static constexpr const BasicVector2 Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept;
    static constexpr _ValueType Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    constexpr _ValueType Dot(const BasicVector2& v) noexcept;
    static _ValueType Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    static _ValueType Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept;
    _ValueType& At(std::size_t index);
    const _ValueType& At(std::size_t index) const;
    _ValueType Length() const noexcept;
    _ValueType LengthSq() const noexcept;
    void Normalize();
    const BasicVector2 Normalized() const;
    
    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The buffer size of destBuffer.
     * @return  The length of string.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/**@section Variable */
public:
	_ValueType x, y;
};

using Vector2 = BasicVector2<float>;
using DVector2 = BasicVector2<double>;
    
template <typename _ValueType>
constexpr BasicVector2<_ValueType>::BasicVector2() noexcept :
    x(0.0f),
    y(0.0f)
{
}

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
constexpr const AddExpression<BasicVector2<_ValueType>, BasicVector2<_ValueType>> BasicVector2<_ValueType>::operator+(const BasicVector2& v) const noexcept
{
    return { *this, v };
}

template <typename _ValueType>
constexpr const SubtractExpression<BasicVector2<_ValueType>, BasicVector2<_ValueType>> BasicVector2<_ValueType>::operator-(const BasicVector2& v) const noexcept
{
    return { *this, v };
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
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator+=(const BasicVector2& v) noexcept
{
    x += v.x;
    y += v.y;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator-=(const BasicVector2& v) noexcept
{
    x -= v.x;
    y -= v.y;
    
    return *this;
}
    
template <typename _ValueType>
inline BasicVector2<_ValueType>& BasicVector2<_ValueType>::operator*=(const BasicVector2& v) noexcept
{
    x *= v.x;
    y *= v.y;
    
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
constexpr bool BasicVector2<_ValueType>::operator==(const BasicVector2& v) const noexcept
{
    return (x == v.x && y == v.y);
}

template <typename _ValueType>
constexpr bool BasicVector2<_ValueType>::operator!=(const BasicVector2& v) const noexcept
{
    return !(*this == v);
}

template <typename _ValueType>
inline _ValueType& BasicVector2<_ValueType>::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector2<_ValueType>::operator[](std::size_t index) const noexcept
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
    return (v1.x * v2.x) + (v1.y * v2.y);
}

template <typename _ValueType>
constexpr _ValueType BasicVector2<_ValueType>::Dot(const BasicVector2& v) noexcept
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
inline _ValueType& BasicVector2<_ValueType>::At(std::size_t index)
{
    assert((index < 2 && index > -1) && "BasicVector2 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector2<_ValueType>::At(std::size_t index) const
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
template <std::size_t _StrBufferSize>
inline int32_t BasicVector2<_ValueType>::ToString(char(&destStr)[_StrBufferSize]) const
{
    this->ToString(destStr, sizeof(destStr));
}

template <typename _ValueType>
inline int32_t BasicVector2<_ValueType>::ToString(char* destStr, std::size_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
}

} /* namespace tgon */

#undef TGON_SPRINTF