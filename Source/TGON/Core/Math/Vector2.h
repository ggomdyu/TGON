/**
 * @file    Vector2.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"
#include "Core/Utility/ExpressionTemplate.h"

namespace tgon
{

struct TGON_API Vector2
{
/* @section Public constructor */
public:
    /* @brief   Initializes x, y components to 0. */
    constexpr Vector2() noexcept;

    /* @brief   Initializes x, y components with the specified value. */
    constexpr Vector2(float scalar) noexcept;

    /* @brief   Initializes x, y components with the specified value. */
    constexpr Vector2(float x, float y) noexcept;

    /* @brief   Initializes x, y components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr Vector2(const BaseExpression<_DerivedExpressionType>& expression);

/* @section Public perator */
public:
    constexpr const AddExpression<Vector2, Vector2> operator+(const Vector2& v) const noexcept;
    constexpr const SubtractExpression<Vector2, Vector2> operator-(const Vector2& v) const noexcept;
    friend constexpr const Vector2 operator*(float scalar, const Vector2& v) noexcept;
    constexpr const Vector2 operator*(float scalar) const noexcept;
    constexpr const Vector2 operator-(float scalar) const;
    constexpr const Vector2 operator+(float scalar) const;
    constexpr const Vector2 operator/(float scalar) const;
    constexpr const Vector2 operator-() const noexcept;
    Vector2& operator+=(const Vector2& v) noexcept;
    Vector2& operator-=(const Vector2& v) noexcept;
    Vector2& operator*=(const Vector2& v) noexcept;
    Vector2& operator*=(float scalar) noexcept;
    Vector2& operator/=(float scalar);
    constexpr bool operator==(const Vector2& v) const noexcept;
    constexpr bool operator!=(const Vector2& v) const noexcept;
    float& operator[](std::size_t index) noexcept;
    float operator[](std::size_t index) const noexcept;
    
/* @section Public method */
public:
    static constexpr const Vector2 Reflect(const Vector2& inDirection, const Vector2& inPlaneNormal) noexcept;
    static constexpr float Dot(const Vector2& v1, const Vector2& v2) noexcept;
    //static float Angle(const Vector2& v1, const Vector2& v2) noexcept;
    static float Distance(const Vector2& v1, const Vector2& v2) noexcept;
    float& At(std::size_t index);
    float At(std::size_t index) const;
    float Length() const noexcept;
    float LengthSq() const noexcept;
    void Normalize();
    const Vector2 Normalized() const;

    /**
     * @brief                   Converts value to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return                  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief                       Converts value to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destBuffer.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/* @section Public variable */
public:
	float x, y;
};


constexpr Vector2::Vector2() noexcept :
    x(0.0f),
    y(0.0f)
{
}

constexpr Vector2::Vector2(float scalar) noexcept :
    x(scalar),
    y(scalar)
{
}

constexpr Vector2::Vector2(float x, float y) noexcept :
    x(x),
	y(y)
{
}

template <typename _DerivedExpressionType>
constexpr Vector2::Vector2(const BaseExpression<_DerivedExpressionType>& expression) :
    x(expression[0]),
    y(expression[1])
{
}

constexpr const AddExpression<Vector2, Vector2> Vector2::operator+(const Vector2& v) const noexcept
{
    return { *this, v };
}

constexpr const SubtractExpression<Vector2, Vector2> Vector2::operator-(const Vector2& v) const noexcept
{
    return { *this, v };
}

constexpr const Vector2 Vector2::operator*(float scalar) const noexcept
{
    return Vector2(x * scalar, y * scalar);
}

constexpr const Vector2 operator*(float scalar, const Vector2& v) noexcept
{
    return v * scalar;
}

constexpr const Vector2 Vector2::operator+(float scalar) const
{
    return Vector2(x + scalar, y + scalar);
}

constexpr const Vector2 Vector2::operator-(float scalar) const
{
    return Vector2(x - scalar, y - scalar);
}

constexpr const Vector2 Vector2::operator/(float scalar) const
{
    return Vector2(x / scalar, y / scalar);
}

constexpr const Vector2 Vector2::operator-() const noexcept
{
    return Vector2(-x, -y);
}

constexpr bool Vector2::operator==(const Vector2& v) const noexcept
{
    return (x == v.x && y == v.y);
}

constexpr bool Vector2::operator!=(const Vector2& v) const noexcept
{
    return !(*this == v);
}

constexpr const Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inPlaneNormal) noexcept
{
    return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
}

constexpr float Vector2::Dot(const Vector2& v1, const Vector2& v2) noexcept
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

} /* namespace tgon */
