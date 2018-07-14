/**
 * @file    Vector3.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"
#include "Core/Utility/ExpressionTemplate.h"

#include "Vector2.h"

namespace tgon
{

struct Vector2;

struct TGON_API Vector3
{
/* @section Public constructor */
public:
    /* @brief   Initializes x, y, z components to 0. */
    constexpr Vector3() noexcept;

    /* @brief   Initializes x, y, z components with the specified value. */
    constexpr Vector3(float scalar) noexcept;

    /* @brief   Initializes x, y, z components with the specified value. */
    constexpr Vector3(float x, float y, float z) noexcept;

    /* @brief   Initializes x, y components with the specified vector and sets z to zero. */
    constexpr Vector3(const Vector2& v) noexcept;

    /* @brief   Initializes x, y components with the specified value and sets z to zero. */
    constexpr Vector3(float x, float y) noexcept;

    /* @brief   Initializes x, y, z components with the specified expression template. */
    template <typename _DerivedExpressionType>
    constexpr Vector3(const BaseExpression<_DerivedExpressionType>& expression);

/* @section Public perator */
public:
    constexpr const AddExpression<Vector3, Vector3> operator+(const Vector3& v) const noexcept;
    constexpr const SubtractExpression<Vector3, Vector3> operator-(const Vector3& v) const noexcept;
    friend constexpr const Vector3 operator*(float scalar, const Vector3& v) noexcept;
    constexpr const Vector3 operator*(float scalar) const noexcept;
    constexpr const Vector3 operator-(float scalar) const;
    constexpr const Vector3 operator+(float scalar) const;
    constexpr const Vector3 operator/(float scalar) const;
    constexpr const Vector3 operator-() const noexcept;
    Vector3& operator+=(const Vector3& v) noexcept;
    Vector3& operator-=(const Vector3& v) noexcept;
    Vector3& operator*=(const Vector3& v) noexcept;
    Vector3& operator*=(float scalar) noexcept;
    Vector3& operator/=(float scalar);
    constexpr bool operator==(const Vector3& v) const noexcept;
    constexpr bool operator!=(const Vector3& v) const noexcept;
    float& operator[](std::size_t index) noexcept;
    float operator[](std::size_t index) const noexcept;
    
/* @section Public method */
public:
    static constexpr const Vector3 Reflect(const Vector3& inDirection, const Vector3& inPlaneNormal) noexcept;
    static constexpr float Dot(const Vector3& v1, const Vector3& v2) noexcept;
    static constexpr const Vector3 Cross(const Vector3& v1, const Vector3& v2) noexcept;
    //static float Angle(const Vector3& v1, const Vector3& v2) noexcept;
    static float Distance(const Vector3& v1, const Vector3& v2) noexcept;
    float& At(std::size_t index);
    float At(std::size_t index) const;
    float Length() const noexcept;
    float LengthSq() const noexcept;
    void Normalize();
    const Vector3 Normalized() const;

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
	float x, y, z;
};


constexpr Vector3::Vector3() noexcept :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

constexpr Vector3::Vector3(float scalar) noexcept :
    x(scalar),
    y(scalar),
    z(scalar)
{
}

constexpr Vector3::Vector3(float x, float y, float z) noexcept :
    x(x),
	y(y), 
	z(z)
{
}

constexpr Vector3::Vector3(float x, float y) noexcept :
    x(x),
    y(y),
    z(0.0f)
{
}

constexpr Vector3::Vector3(const Vector2& v) noexcept :
    x(v.x),
    y(v.y),
    z(0.0f)
{
}

template <typename _DerivedExpressionType>
constexpr Vector3::Vector3(const BaseExpression<_DerivedExpressionType>& expression) :
    x(expression[0]),
    y(expression[1]),
    z(expression[2])
{
}

constexpr const AddExpression<Vector3, Vector3> Vector3::operator+(const Vector3& vec) const noexcept
{
    return {*this, vec};
}

constexpr const SubtractExpression<Vector3, Vector3> Vector3::operator-(const Vector3& vec) const noexcept
{
    return {*this, vec};
}

constexpr const Vector3 Vector3::operator*(float scalar) const noexcept
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

constexpr const Vector3 operator*(float lhs, const Vector3& vec) noexcept
{
	return vec * lhs;
}

constexpr const Vector3 Vector3::operator+(float scalar) const
{
    return Vector3(x + scalar, y + scalar, z + scalar);
}

constexpr const Vector3 Vector3::operator-(float scalar) const
{
    return Vector3(x - scalar, y - scalar, z - scalar);
}

constexpr const Vector3 Vector3::operator/(float scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

constexpr const Vector3 Vector3::operator-() const noexcept
{
	return Vector3(-x, -y, -z);
}

constexpr bool Vector3::operator==(const Vector3& vec) const noexcept
{
	return (x == vec.x && y == vec.y && z == vec.z);
}

constexpr bool Vector3::operator!=(const Vector3& vec) const noexcept
{
    return !(*this == vec);
}

constexpr const Vector3 Vector3::Reflect(const Vector3& inDirection, const Vector3& inPlaneNormal) noexcept
{
    return inDirection + Dot(-inDirection, inPlaneNormal) * 2 * inPlaneNormal;
}

constexpr float Vector3::Dot(const Vector3& v1, const Vector3& v2) noexcept
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

constexpr const Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2) noexcept
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

} /* namespace tgon */
