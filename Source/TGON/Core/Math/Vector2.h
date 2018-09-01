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

#include "Core/Platform/Config.h"
#include "Core/Utility/ExpressionTemplate.h"

namespace tgon
{
    
template <typename _ValueType,
          typename std::enable_if<std::is_floating_point<_ValueType>::value>::type* = nullptr>
struct TGON_API BasicVector2
{
/* @section Public constructor */
public:
    /* @brief   Initializes x, y components to 0. */
    constexpr BasicVector2() noexcept :
        x(0.0f),
        y(0.0f)
    {
    }

    /* @brief   Initializes x, y components with the specified value. */
    constexpr BasicVector2(const _ValueType& scalar) noexcept :
        x(scalar),
        y(scalar)
    {
    }

    /* @brief   Initializes x, y components with the specified value. */
    constexpr BasicVector2(const _ValueType& x, const _ValueType& y) noexcept :
        x(x),
        y(y)
    {
    }

    /* @brief   Initializes x, y components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr BasicVector2(const BaseExpression<_DerivedExpressionType>& expression) :
        x(expression[0]),
        y(expression[1])
    {
    }

/* @section Public perator */
public:
    constexpr const AddExpression<BasicVector2, BasicVector2> operator+(const BasicVector2& v) const noexcept
    {
        return { *this, v };
    }
    
    constexpr const SubtractExpression<BasicVector2, BasicVector2> operator-(const BasicVector2& v) const noexcept
    {
        return { *this, v };
    }
    
    friend constexpr const BasicVector2 operator*(const _ValueType& scalar, const BasicVector2& v) noexcept
    {
        return v * scalar;
    }
    
    constexpr const BasicVector2 operator*(const _ValueType& scalar) const noexcept
    {
        return BasicVector2(x * scalar, y * scalar);
    }
    
    constexpr const BasicVector2 operator-(const _ValueType& scalar) const
    {
        return BasicVector2(x - scalar, y - scalar);
    }

    constexpr const BasicVector2 operator+(const _ValueType& scalar) const
    {
        return BasicVector2(x + scalar, y + scalar);
    }

    constexpr const BasicVector2 operator/(const _ValueType& scalar) const
    {
        return BasicVector2(x / scalar, y / scalar);
    }
    
    constexpr const BasicVector2 operator-() const noexcept
    {
        return BasicVector2(-x, -y);
    }
    
    BasicVector2& operator+=(const BasicVector2& v) noexcept
    {
        x += v.x;
        y += v.y;
        
        return *this;
    }
    
    BasicVector2& operator-=(const BasicVector2& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        
        return *this;
    }
    
    BasicVector2& operator*=(const BasicVector2& v) noexcept
    {
        x *= v.x;
        y *= v.y;
        
        return *this;
    }
    
    BasicVector2& operator*=(_ValueType scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        
        return *this;
    }
    
    BasicVector2& operator/=(_ValueType scalar)
    {
        x /= scalar;
        y /= scalar;
        
        return *this;
    }
    
    constexpr bool operator==(const BasicVector2& v) const noexcept
    {
        return (x == v.x && y == v.y);
    }

    constexpr bool operator!=(const BasicVector2& v) const noexcept
    {
        return !(*this == v);
    }

    _ValueType& operator[](std::size_t index) noexcept
    {
        return *(&x + index);
    }
    
    const _ValueType& operator[](std::size_t index) const noexcept
    {
        return *(&x + index);
    }
    
/* @section Public method */
public:
    static constexpr const BasicVector2 Reflect(const BasicVector2& inDirection, const BasicVector2& inPlaneNormal) noexcept
    {
        return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
    }
    
    static constexpr _ValueType Dot(const BasicVector2& v1, const BasicVector2& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }
    
    constexpr _ValueType Dot(const BasicVector2& v) noexcept
    {
        return (x * v.x) + (y * v.y);
    }
    
    static _ValueType Angle(const BasicVector2& v1, const BasicVector2& v2) noexcept
    {
        return std::acos(v1.Dot(v2) / (v1.Length() * v2.Length()));
    }
    
    static _ValueType Distance(const BasicVector2& v1, const BasicVector2& v2) noexcept
    {
        return BasicVector2(v1 - v2).Length();
    }
    
    _ValueType& At(std::size_t index)
    {
        assert((index < 2 && index > -1) && "BasicVector2 index out of range");
        
        return *(&x + index);
    }
    
    const _ValueType& At(std::size_t index) const
    {
        assert((index < 2 && index > -1) && "BasicVector2 index out of range");
        
        return *(&x + index);
    }
    
    _ValueType Length() const noexcept
    {
        return std::sqrtf(this->LengthSq());
    }
    
    _ValueType LengthSq() const noexcept
    {
        return (x * x) + (y * y);
    }
    
    void Normalize()
    {
        *this = this->Normalized();
    }
    
    const BasicVector2 Normalized() const
    {
        _ValueType length = this->Length();
        
        return Vector3(x / length, y / length);
    }

    /**
     * @brief                   Converts value to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return                  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const
    {
        this->ToString(destStr, _StrBufferSize);
    }

    /**
     * @brief                       Converts value to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destBuffer.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const
    {
#if _MSC_VER
        return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#else
        return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#endif
    }

/* @section Public variable */
public:
	_ValueType x, y;
};

using Vector2 = BasicVector2<float>;
using DVector2 = BasicVector2<double>;

} /* namespace tgon */
