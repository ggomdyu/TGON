/**
 * @file    Vector3.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cmath>

#include "Misc/ExpressionTemplate.h"

#include "Vector2.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF sprintf
#endif

namespace tgon
{

template <typename _ValueType>
struct BasicVector3 final
{
/**@section Constructor */
public:
    /**@brief   Initializes x, y, z components to 0. */
    constexpr BasicVector3() noexcept;
    
    /**@brief   Initializes x, y, z components with the specified value. */
    constexpr BasicVector3(const _ValueType& scalar) noexcept;

    /**@brief   Initializes x, y, z components with the specified value. */
    constexpr BasicVector3(const _ValueType& x, const _ValueType& y, const _ValueType& z) noexcept;

    /**@brief   Initializes x, y components with the specified value and sets z to zero. */
    constexpr BasicVector3(const _ValueType& x, const _ValueType& y) noexcept;

    /**@brief   Initializes x, y, z components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr BasicVector3(const BaseExpression<_DerivedExpressionType>& expression);
    
/**@section Operator */
public:
    constexpr const AddExpression<BasicVector3, BasicVector3> operator+(const BasicVector3& rhs) const noexcept;
    constexpr const SubtractExpression<BasicVector3, BasicVector3> operator-(const BasicVector3& rhs) const noexcept;
    constexpr const BasicVector3 operator+(const _ValueType& rhs) const;
    constexpr const BasicVector3 operator-(const _ValueType& rhs) const;
    constexpr const BasicVector3 operator*(const _ValueType& rhs) const noexcept;
    constexpr const BasicVector3 operator/(const _ValueType& rhs) const;
    constexpr const BasicVector3 operator-() const noexcept;
    friend constexpr const BasicVector3 operator*(const _ValueType& scalar, const BasicVector3& v) noexcept;
    BasicVector3& operator+=(const BasicVector3& rhs) noexcept;
    BasicVector3& operator-=(const BasicVector3& rhs) noexcept;
    BasicVector3& operator*=(const BasicVector3& rhs) noexcept;
    BasicVector3& operator*=(const _ValueType& rhs) noexcept;
    BasicVector3& operator/=(const _ValueType& rhs);
    _ValueType& operator[](std::size_t index) noexcept;
    const _ValueType& operator[](std::size_t index) const noexcept;
    constexpr bool operator==(const BasicVector3& rhs) const noexcept;
    constexpr bool operator!=(const BasicVector3& rhs) const noexcept;
    constexpr operator Vector2() const noexcept;
    
/**@section Method */
public:
    static constexpr const BasicVector3 Reflect(const BasicVector3& inDirection, const BasicVector3& inPlaneNormal) noexcept;
    static constexpr _ValueType Dot(const BasicVector3& v1, const BasicVector3& v2) noexcept;
    constexpr _ValueType Dot(const BasicVector3& v) const noexcept;
    static constexpr const BasicVector3 Cross(const BasicVector3& v1, const BasicVector3& v2) noexcept;
    _ValueType& At(std::size_t index);
    const _ValueType& At(std::size_t index) const;
    //static float Angle(const BasicVector3& v1, const BasicVector3& v2) noexcept;
    static _ValueType Distance(const BasicVector3& v1, const BasicVector3& v2);
    _ValueType Distance(const BasicVector3& v) const noexcept;
    _ValueType Length() const;
    _ValueType LengthSq() const noexcept;
    void Normalize();
    const BasicVector3 Normalized() const;
    
    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string.
     */
    template <std::size_t _DestStrBufferLen>
    int32_t ToString(char(&destStr)[_DestStrBufferLen]) const;

    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr             The destination of the string to be written.
     * @param [in] destStrBufferLen     The buffer size of destBuffer.
     * @return  The length of string.
     */
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    
/**@section Variable */
public:
	_ValueType x, y, z;
};
    
using Vector3 = BasicVector3<float>;
using DVector3 = BasicVector3<double>;

template <typename... _Types>
BasicVector3(_Types...) -> BasicVector3<std::common_type_t<_Types...>>;

template <typename _ValueType>
constexpr BasicVector3<_ValueType>::BasicVector3() noexcept  :
    BasicVector3(0.0f, 0.0f, 0.0f)
{
}

template <typename _ValueType>
constexpr BasicVector3<_ValueType>::BasicVector3(const _ValueType& scalar) noexcept :
    BasicVector3(scalar, scalar, scalar)
{
}

template <typename _ValueType>
constexpr BasicVector3<_ValueType>::BasicVector3(const _ValueType& x, const _ValueType& y, const _ValueType& z) noexcept :
    x(x),
    y(y),
    z(z)
{
}

template <typename _ValueType>
constexpr BasicVector3<_ValueType>::BasicVector3(const _ValueType& x, const _ValueType& y) noexcept :
    BasicVector3(x, y, 0.0f)
{
}

template <typename _ValueType>
template <typename _DerivedExpressionType>
constexpr BasicVector3<_ValueType>::BasicVector3(const BaseExpression<_DerivedExpressionType>& expression) :
    BasicVector3(expression[0], expression[1], expression[2])
{
}

template <typename _ValueType>
constexpr const AddExpression<BasicVector3<_ValueType>, BasicVector3<_ValueType>> BasicVector3<_ValueType>::operator+(const BasicVector3& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const SubtractExpression<BasicVector3<_ValueType>, BasicVector3<_ValueType>> BasicVector3<_ValueType>::operator-(const BasicVector3& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::operator+(const _ValueType& rhs) const
{
    return BasicVector3(x + rhs, y + rhs, z + rhs);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::operator-(const _ValueType& rhs) const
{
    return BasicVector3(x - rhs, y - rhs, z - rhs);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicVector3(x * rhs, y * rhs, z * rhs);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicVector3(x / rhs, y / rhs, z / rhs);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::operator-() const noexcept
{
    return BasicVector3(-x, -y, -z);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> operator*(const _ValueType& scalar, const BasicVector3<_ValueType>& v) noexcept
{
    return v * scalar;
}

template <typename _ValueType>
inline BasicVector3<_ValueType>& BasicVector3<_ValueType>::operator+=(const BasicVector3& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector3<_ValueType>& BasicVector3<_ValueType>::operator-=(const BasicVector3& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector3<_ValueType>& BasicVector3<_ValueType>::operator*=(const BasicVector3& rhs) noexcept
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector3<_ValueType>& BasicVector3<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector3<_ValueType>& BasicVector3<_ValueType>::operator/=(const _ValueType& rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    
    return *this;
}

template <typename _ValueType>
inline _ValueType& BasicVector3<_ValueType>::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector3<_ValueType>::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
constexpr bool BasicVector3<_ValueType>::operator==(const BasicVector3& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y && z == rhs.z);
}

template <typename _ValueType>
constexpr bool BasicVector3<_ValueType>::operator!=(const BasicVector3& rhs) const noexcept
{
    return !(*this == rhs);
}
    
template <typename _ValueType>
inline constexpr BasicVector3<_ValueType>::operator Vector2() const noexcept
{
    return Vector2(x, y);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::Reflect(const BasicVector3& inDirection, const BasicVector3& inPlaneNormal) noexcept
{
    return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
}

template <typename _ValueType>
constexpr _ValueType BasicVector3<_ValueType>::Dot(const BasicVector3& v1, const BasicVector3& v2) noexcept
{
    return v1.Dot(v2);
}
    
template <typename _ValueType>
constexpr _ValueType BasicVector3<_ValueType>::Dot(const BasicVector3& v) const noexcept
{
    return (x * v.x) + (y * v.y) + (z * v.z);
}

template <typename _ValueType>
constexpr const BasicVector3<_ValueType> BasicVector3<_ValueType>::Cross(const BasicVector3& v1, const BasicVector3& v2) noexcept
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

template <typename _ValueType>
inline _ValueType& BasicVector3<_ValueType>::At(std::size_t index)
{
    assert((index < 3 && index > -1) && "BasicVector3 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline const _ValueType& BasicVector3<_ValueType>::At(std::size_t index) const
{
    assert((index < 3 && index > -1) && "BasicVector3 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector3<_ValueType>::Distance(const BasicVector3& v1, const BasicVector3& v2)
{
    return BasicVector3(v1 - v2).Length();
}
    
template <typename _ValueType>
inline _ValueType BasicVector3<_ValueType>::Distance(const BasicVector3& v) const noexcept
{
    return BasicVector3(*this - v).Length();
}

template <typename _ValueType>
inline _ValueType BasicVector3<_ValueType>::Length() const
{
    return std::sqrtf(this->LengthSq());
}

template <typename _ValueType>
inline _ValueType BasicVector3<_ValueType>::LengthSq() const noexcept
{
    return (x * x) + (y * y) + (z * z);
}

template <typename _ValueType>
inline void BasicVector3<_ValueType>::Normalize()
{
    *this = this->Normalized();
}

template <typename _ValueType>
inline const BasicVector3<_ValueType> BasicVector3<_ValueType>::Normalized() const
{
    _ValueType length = this->Length();
    
    return BasicVector3(x / length, y / length, z / length);
}

template <typename _ValueType>
template <std::size_t _DestStrBufferLen>
inline int32_t BasicVector3<_ValueType>::ToString(char(&destStr)[_DestStrBufferLen]) const
{
    return this->ToString(destStr, sizeof(destStr));
}

template <typename _ValueType>
inline int32_t BasicVector3<_ValueType>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f %f", x, y, z);
}
    
} /* namespace tgon */

#undef TGON_SPRINTF
