/**
 * @filename    Vector2.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Utility/ExpressionTemplate.h"

#include <cassert>
#include <cstdint>
#include <cmath>
#include <cstdio>

namespace tgon
{
namespace core
{

struct TGON_API Vector2
{
/* @section Public constructor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Vector2() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Vector2(float scalar) noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Vector2(float x, float y) noexcept;

    template <typename _DerivedExpressionType>
    constexpr Vector2(const BaseExpression<_DerivedExpressionType>& expression);

/* @section Public perator */
public:
    constexpr const AddExpression<Vector2, Vector2> operator+(const Vector2& rhs) const noexcept;
    constexpr const SubtractExpression<Vector2, Vector2> operator-(const Vector2& rhs) const noexcept;
    friend constexpr const Vector2 operator*(float, const Vector2& rhs) noexcept;
    constexpr const Vector2 operator*(float) const noexcept;
    constexpr const Vector2 operator-(float) const;
    constexpr const Vector2 operator+(float) const;
    constexpr const Vector2 operator/(float) const;
    constexpr const Vector2 operator-() const noexcept;
    Vector2& operator+=(const Vector2&) noexcept;
    Vector2& operator-=(const Vector2&) noexcept;
    Vector2& operator*=(const Vector2&) noexcept;
    Vector2& operator*=(float) noexcept;
    Vector2& operator/=(float);
    constexpr bool operator==(const Vector2&) const noexcept;
    constexpr bool operator!=(const Vector2&) const noexcept;
    float& operator[](std::size_t index) noexcept;
    float operator[](std::size_t index) const noexcept;
    
/* @section Public method */
public:
    static constexpr float Dot(const Vector2& a, const Vector2& b) noexcept;
    static float Angle(const Vector2& a, const Vector2& b) noexcept;
    static float Distance(const Vector2& a, const Vector2& b) noexcept;
    float& At(std::size_t index);
    float At(std::size_t index) const;
    float Length() const noexcept;
    constexpr float LengthSq() const noexcept;
    void Normalize();
    constexpr const Vector2 Normalized() const;

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

constexpr tgon::core::Vector2::Vector2(float scalar) noexcept :
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

constexpr const AddExpression<Vector2, Vector2> Vector2::operator+(const Vector2& rhs) const noexcept
{
    return {*this, rhs};
}

constexpr const SubtractExpression<Vector2, Vector2> Vector2::operator-(const Vector2& rhs) const noexcept
{
    return {*this, rhs};
}

constexpr const Vector2 Vector2::operator*(float rhs) const noexcept
{
    return Vector2(x * rhs, y * rhs);
}

constexpr const Vector2 operator*(float lhs, const Vector2& rhs) noexcept
{
	return rhs * lhs;
}

constexpr const Vector2 Vector2::operator+(float rhs) const
{
    return Vector2(x + rhs, y + rhs);
}

constexpr const Vector2 Vector2::operator-(float rhs) const
{
    return Vector2(x - rhs, y - rhs);
}

constexpr const Vector2 Vector2::operator/(float rhs) const
{
    return Vector2(x / rhs, y / rhs);
}

constexpr const Vector2 Vector2::operator-() const noexcept
{
	return Vector2(-x, -y);
}

inline Vector2& Vector2::operator+=(const Vector2& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& rhs) noexcept
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& rhs) noexcept
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

inline Vector2& Vector2::operator*=(float rhs) noexcept
{
	x *= rhs;
	y *= rhs;

	return *this;
}

inline Vector2& Vector2::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}

constexpr bool Vector2::operator==(const Vector2& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y);
}

constexpr bool Vector2::operator!=(const Vector2& rhs) const noexcept
{
    return !(*this == rhs);
}

inline float& Vector2::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

inline float Vector2::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

inline float& Vector2::At(std::size_t index)
{
    assert((index < 2 && index > -1) && "Vector2 index out of range");

    return *(&x + index);
}

inline float Vector2::At(std::size_t index) const
{
    assert((index < 2 && index > -1) && "Vector2 index out of range");

    return *(&x + index);
}

constexpr float Vector2::Dot(const Vector2& v1, const Vector2& v2) noexcept
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

inline float Vector2::Distance(const Vector2& v1, const Vector2& v2) noexcept
{
    return Vector2(v1 - v2).Length();
}

inline float Vector2::Length() const noexcept
{
    return std::sqrtf((x * x) + (y * y));
}

constexpr float Vector2::LengthSq() const noexcept
{
	return (x * x) + (y * y);
}

inline void Vector2::Normalize()
{
    float length = std::sqrtf((x * x) + (y * y));

	x /= length;
	y /= length;
}

template <std::size_t _StrBufferSize>
inline int32_t Vector2::ToString(char(&destStr)[_StrBufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destStr, "%f %f", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * _StrBufferSize, "%f %f", x, y);
#endif
}

inline int32_t Vector2::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#endif
}

} /* namespace core */
} /* namespace tgon */