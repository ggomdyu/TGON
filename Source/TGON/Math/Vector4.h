/**
 * @file    Vector4.h
 * @author  ggomdyu
 * @since   05/18/2019
 */

#pragma once
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cmath>

#include "Core/ExpressionTemplate.h"

#include "Vector3.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF sprintf
#endif

namespace tgon
{

template <typename _ValueType>
struct BasicVector4 final
{
/**@section Constructor */
public:
    /**@brief   Initializes x, y, z, w components to 0. */
    constexpr BasicVector4() noexcept;
    
    /**@brief   Initializes x, y, z, w components with the specified value. */
    constexpr BasicVector4(const _ValueType& scalar) noexcept;

    /**@brief   Initializes x, y, z, w components with the specified value. */
    constexpr BasicVector4(const _ValueType& x, const _ValueType& y, const _ValueType& z, const _ValueType& w) noexcept;

    /**@brief   Initializes x, y, z, w components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr BasicVector4(const BaseExpression<_DerivedExpressionType>& expression);
    
/**@section Operator */
public:
    constexpr const AddExpression<BasicVector4, BasicVector4> operator+(const BasicVector4& v) const noexcept;
    constexpr const SubtractExpression<BasicVector4, BasicVector4> operator-(const BasicVector4& v) const noexcept;
    constexpr const BasicVector4 operator+(const _ValueType& scalar) const noexcept;
    constexpr const BasicVector4 operator-(const _ValueType& scalar) const noexcept;
    constexpr const BasicVector4 operator*(const _ValueType& scalar) const noexcept;
    constexpr const BasicVector4 operator/(const _ValueType& scalar) const;
    constexpr const BasicVector4 operator-() const noexcept;
    friend constexpr const BasicVector4 operator*(const _ValueType& scalar, const BasicVector4& v) noexcept;
    BasicVector4& operator+=(const BasicVector4& v) noexcept;
    BasicVector4& operator-=(const BasicVector4& v) noexcept;
    BasicVector4& operator*=(const BasicVector4& v) noexcept;
    BasicVector4& operator*=(const _ValueType& scalar) noexcept;
    BasicVector4& operator/=(const _ValueType& scalar);
    _ValueType& operator[](std::size_t index) noexcept;
    const _ValueType& operator[](std::size_t index) const noexcept;
    constexpr bool operator==(const BasicVector4& v) const noexcept;
    constexpr bool operator!=(const BasicVector4& v) const noexcept;
    constexpr operator Vector3() const noexcept;
    
/**@section Method */
public:
    static constexpr _ValueType Dot(const BasicVector4& v1, const BasicVector4& v2) noexcept;
    _ValueType& At(std::size_t index);
    const _ValueType& At(std::size_t index) const;
    static _ValueType Distance(const BasicVector4& v1, const BasicVector4& v2) noexcept;
    _ValueType Length() const noexcept;
    _ValueType LengthSq() const noexcept;
    void Normalize();
    const BasicVector4 Normalized() const;
    
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
	_ValueType x, y, z, w;
};
    
using Vector4 = BasicVector4<float>;
using DVector4 = BasicVector4<double>;

template <typename _ValueType>
constexpr BasicVector4<_ValueType>::BasicVector4() noexcept  :
    BasicVector4(0.0f, 0.0f, 0.0f, 0.0f)
{
}

template <typename _ValueType>
constexpr BasicVector4<_ValueType>::BasicVector4(const _ValueType& scalar) noexcept :
    BasicVector4(scalar, scalar, scalar, scalar)
{
}

template <typename _ValueType>
constexpr BasicVector4<_ValueType>::BasicVector4(const _ValueType& x, const _ValueType& y, const _ValueType& z, const _ValueType& w) noexcept :
    x(x),
    y(y),
    z(z),
    w(w)
{
}

template <typename _ValueType>
template <typename _DerivedExpressionType>
constexpr BasicVector4<_ValueType>::BasicVector4(const BaseExpression<_DerivedExpressionType>& expression) :
    BasicVector4(expression[0], expression[1], expression[2], expression[3])
{
}

template <typename _ValueType>
constexpr const AddExpression<BasicVector4<_ValueType>, BasicVector4<_ValueType>> BasicVector4<_ValueType>::operator+(const BasicVector4& v) const noexcept
{
    return {*this, v};
}

template <typename _ValueType>
constexpr const SubtractExpression<BasicVector4<_ValueType>, BasicVector4<_ValueType>> BasicVector4<_ValueType>::operator-(const BasicVector4& v) const noexcept
{
    return {*this, v};
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator+(const _ValueType& scalar) const noexcept
{
    return BasicVector4(x + scalar, y + scalar, z + scalar, w + scalar);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator-(const _ValueType& scalar) const noexcept
{
    return BasicVector4(x - scalar, y - scalar, z - scalar, w - scalar);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator*(const _ValueType& scalar) const noexcept
{
    return BasicVector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator/(const _ValueType& scalar) const
{
    return BasicVector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator-() const noexcept
{
    return BasicVector4(-x, -y, -z, -w);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> operator*(const _ValueType& scalar, const BasicVector4<_ValueType>& v) noexcept
{
    return v * scalar;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator+=(const BasicVector4& v) noexcept
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator-=(const BasicVector4& v) noexcept
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator*=(const BasicVector4& v) noexcept
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator*=(const _ValueType& scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator/=(const _ValueType& scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    
    return *this;
}

template <typename _ValueType>
inline _ValueType& BasicVector4<_ValueType>::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector4<_ValueType>::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
constexpr bool BasicVector4<_ValueType>::operator==(const BasicVector4& v) const noexcept
{
    return (x == v.x && y == v.y && z == v.z && w == v.w);
}

template <typename _ValueType>
constexpr bool BasicVector4<_ValueType>::operator!=(const BasicVector4& v) const noexcept
{
    return !(*this == v);
}

template<typename _ValueType>
inline constexpr BasicVector4<_ValueType>::operator Vector3() const noexcept
{
    return Vector3(x, y, z);
}

template <typename _ValueType>
constexpr _ValueType BasicVector4<_ValueType>::Dot(const BasicVector4& v1, const BasicVector4& v2) noexcept
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

template <typename _ValueType>
inline _ValueType& BasicVector4<_ValueType>::At(std::size_t index)
{
    assert((index < 4 && index > -1) && "BasicVector4 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector4<_ValueType>::At(std::size_t index) const
{
    assert((index < 4 && index > -1) && "BasicVector4 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::Distance(const BasicVector4& v1, const BasicVector4& v2) noexcept
{
    return BasicVector4(v1 - v2).Length();
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::Length() const noexcept
{
    return std::sqrt(this->LengthSq());
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::LengthSq() const noexcept
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

template <typename _ValueType>
inline void BasicVector4<_ValueType>::Normalize()
{
    *this = this->Normalized();
}

template <typename _ValueType>
inline const BasicVector4<_ValueType> BasicVector4<_ValueType>::Normalized() const
{
    _ValueType length = this->Length();
    
    return BasicVector4(x / length, y / length, z / length, w / length);
}

template <typename _ValueType>
template <std::size_t _StrBufferSize>
inline int32_t BasicVector4<_ValueType>::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, sizeof(destStr));
}

template <typename _ValueType>
inline int32_t BasicVector4<_ValueType>::ToString(char* destStr, std::size_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f, %f", x, y, z, w);
}
    
} /* namespace tgon */

#undef TGON_SPRINTF
