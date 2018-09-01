/**
 * @file    Vector3.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>
#include <cassert>
#include <cstdio>

#include "Core/Platform/Config.h"
#include "Core/Utility/ExpressionTemplate.h"

namespace tgon
{

template <typename _ValueType,
          typename std::enable_if<std::is_floating_point<_ValueType>::value>::type* = nullptr>
struct TGON_API BasicVector3
{
/* @section Public constructor */
public:
    /* @brief   Initializes x, y, z components to 0. */
    constexpr BasicVector3() noexcept  :
        x(0.0f),
        y(0.0f),
        z(0.0f)
    {
    }
    
    /* @brief   Initializes x, y, z components with the specified value. */
    constexpr BasicVector3(const _ValueType& scalar) noexcept :
        x(scalar),
        y(scalar),
        z(scalar)
    {
    }

    /* @brief   Initializes x, y, z components with the specified value. */
    constexpr BasicVector3(const _ValueType& x, const _ValueType& y, const _ValueType& z) noexcept :
        x(x),
        y(y),
        z(z)
    {
    }

    /* @brief   Initializes x, y components with the specified value and sets z to zero. */
    constexpr BasicVector3(const _ValueType& x, const _ValueType& y) noexcept :
        x(x),
        y(y),
        z(0.0f)
    {
    }

    /* @brief   Initializes x, y, z components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr BasicVector3(const BaseExpression<_DerivedExpressionType>& expression) :
        x(expression[0]),
        y(expression[1]),
        z(expression[2])
    {
    }

/* @section Public perator */
public:
    constexpr const AddExpression<BasicVector3, BasicVector3> operator+(const BasicVector3& v) const noexcept
    {
        return {*this, v};
    }
    
    constexpr const SubtractExpression<BasicVector3, BasicVector3> operator-(const BasicVector3& v) const noexcept
    {
        return {*this, v};
    }
    
    constexpr const BasicVector3 operator+(const _ValueType& scalar) const
    {
        return BasicVector3(x + scalar, y + scalar, z + scalar);
    }
    
    constexpr const BasicVector3 operator-(const _ValueType& scalar) const
    {
        return BasicVector3(x - scalar, y - scalar, z - scalar);
    }
    
    constexpr const BasicVector3 operator*(const _ValueType& scalar) const noexcept
    {
        return BasicVector3(x * scalar, y * scalar, z * scalar);
    }
    
    constexpr const BasicVector3 operator/(const _ValueType& scalar) const
    {
        return BasicVector3(x / scalar, y / scalar, z / scalar);
    }
    
    constexpr const BasicVector3 operator-() const noexcept
    {
        return BasicVector3(-x, -y, -z);
    }
    
    friend constexpr const BasicVector3 operator*(const _ValueType& scalar, const BasicVector3& v) noexcept
    {
        return v * scalar;
    }
    
    BasicVector3& operator+=(const BasicVector3& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        
        return *this;
    }
    
    BasicVector3& operator-=(const BasicVector3& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        
        return *this;
    }
    
    BasicVector3& operator*=(const BasicVector3& v) noexcept
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        
        return *this;
    }
    
    BasicVector3& operator*=(const _ValueType& scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        
        return *this;
    }
    
    BasicVector3& operator/=(const _ValueType& scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        
        return *this;
    }
    
    _ValueType& operator[](std::size_t index) noexcept
    {
        return *(&x + index);
    }
    
    const _ValueType& operator[](std::size_t index) const noexcept
    {
        return *(&x + index);
    }
    
    constexpr bool operator==(const BasicVector3& v) const noexcept
    {
        return (x == v.x && y == v.y && z == v.z);
    }
    
    constexpr bool operator!=(const BasicVector3& v) const noexcept
    {
        return !(*this == v);
    }
    
/* @section Public method */
public:
    static constexpr const BasicVector3 Reflect(const BasicVector3& inDirection, const BasicVector3& inPlaneNormal) noexcept
    {
        return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
    }
    
    static constexpr _ValueType Dot(const BasicVector3& v1, const BasicVector3& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }
    
    static constexpr const BasicVector3 Cross(const BasicVector3& v1, const BasicVector3& v2) noexcept
    {
        return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
    }
    
    _ValueType& At(std::size_t index)
    {
        assert((index < 3 && index > -1) && "BasicVector3 index out of range");
        
        return *(&x + index);
    }
    
    const _ValueType& At(std::size_t index) const
    {
        assert((index < 3 && index > -1) && "BasicVector3 index out of range");
        
        return *(&x + index);
    }
    
    //static float Angle(const BasicVector3& v1, const BasicVector3& v2) noexcept;
    
    static _ValueType Distance(const BasicVector3& v1, const BasicVector3& v2) noexcept
    {
        return BasicVector3(v1 - v2).Length();
    }
    
    _ValueType Length() const noexcept
    {
        return std::sqrtf(this->LengthSq());
    }
    
    _ValueType LengthSq() const noexcept
    {
        return (x * x) + (y * y) + (z * z);
    }
    
    void Normalize()
    {
        *this = this->Normalized();
    }
    
    const BasicVector3 Normalized() const
    {
        _ValueType length = this->Length();
        
        return BasicVector3(x / length, y / length, z / length);
    }
    
    /**
     * @brief   Converts value to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const
    {
        this->ToString(destStr, _StrBufferSize);
    }

    /**
     * @brief   Converts value to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destBuffer.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const
    {
#if _MSC_VER
        return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", x, y, z);
#else
        return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", x, y, z);
#endif
    }

/* @section Public variable */
public:
	_ValueType x, y, z;
};
    
using Vector3 = BasicVector3<float>;
using DVector3 = BasicVector3<double>;

} /* namespace tgon */
