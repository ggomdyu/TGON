/**
 * @filename    Vector3.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cassert>
#include <cstddef>
#include <cmath>

namespace tgon
{
namespace math
{

struct TGON_API Vector3
{
/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Vector3() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Vector3(float x, float y, float z) noexcept;

/* @section Operator */
public:
    constexpr const Vector3 operator+(const Vector3&) const noexcept;
    constexpr const Vector3 operator-(const Vector3&) const noexcept;
    constexpr const Vector3 operator*(const Vector3&) const noexcept;
    friend constexpr const Vector3 operator*(float, const Vector3& rhs) noexcept;
    constexpr const Vector3 operator*(float) const noexcept;
    const Vector3 operator/(float) const;
    constexpr const Vector3 operator+() const noexcept;
    constexpr const Vector3 operator-() const noexcept;
    Vector3& operator+=(const Vector3&) noexcept;
    Vector3& operator-=(const Vector3&) noexcept;
    Vector3& operator*=(const Vector3&) noexcept;
    Vector3& operator*=(float) noexcept;
    Vector3& operator/=(float);
    constexpr bool operator==(const Vector3&) const noexcept;
    constexpr bool operator!=(const Vector3&) const noexcept;
    float& operator[](std::size_t) noexcept;
    float operator[](std::size_t) const noexcept;
	
/* @section Public method */
public:
    static constexpr float Dot(const Vector3& a, const Vector3& b) noexcept;
    static constexpr const Vector3 Cross(const Vector3& a, const Vector3& b) noexcept;
    static float Angle(const Vector3& a, const Vector3& b) noexcept;
    static float Distance(const Vector3& a, const Vector3& b) noexcept;
    float& At(std::size_t index);
    float At(std::size_t index) const;
    float Length() const noexcept;
    constexpr float LengthSq() const noexcept;
    void Normalize();
    const Vector3 Normalized() const;
    void TransformCoord(const struct TMatrix4x4&) noexcept;
    void TransformNormal(const struct TMatrix4x4&) noexcept;

/* @section Public variable */
public:
	float x, y, z;

    static const Vector3 Forward;   // 0, 0, 1
	static const Vector3 Back;      // 0, 0, -1
	static const Vector3 Up;        // 0, 1, 0
	static const Vector3 Down;      // 0, -1, 0
	static const Vector3 Left;      // -1, 0, 0
	static const Vector3 Right;     // 1, 0, 0
	static const Vector3 One;		// 0, 0, 0
	static const Vector3 Zero;      // 1, 1, 1
};

constexpr Vector3::Vector3() noexcept :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

constexpr Vector3::Vector3(float x, float y, float z) noexcept :
    x(x),
	y(y), 
	z(z)
{
}

constexpr const Vector3 Vector3::operator+(const Vector3& rhs) const noexcept
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

constexpr const Vector3 Vector3::operator-(const Vector3& rhs) const noexcept
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

constexpr const Vector3 Vector3::operator*(const Vector3& rhs) const noexcept
{
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

constexpr const Vector3 Vector3::operator*(float scalar) const noexcept
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

constexpr const Vector3 operator*(float lhs, const Vector3& rhs) noexcept
{
	return rhs * lhs;
}

inline const Vector3 Vector3::operator/(float value) const
{
    float inverse = 1.0f / value;
    return Vector3(x * inverse, y * inverse, z * inverse);
}

constexpr const Vector3 Vector3::operator+() const noexcept
{
	return *this;
}

constexpr const Vector3 Vector3::operator-() const noexcept
{
	return Vector3(-x, -y, -z);
}

inline Vector3& Vector3::operator+=(const Vector3& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& rhs) noexcept
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& rhs) noexcept
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=(float scalar) noexcept
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

inline Vector3& Vector3::operator/=(float scalar)
{
	float inverse = 1.0f / scalar;

	x *= inverse;
	y *= inverse;
	z *= inverse;

	return *this;
}

constexpr bool Vector3::operator==(const Vector3& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

constexpr bool Vector3::operator!=(const Vector3& rhs) const noexcept
{
    return (x != rhs.x && y != rhs.y && z != rhs.z);
}

inline float& Vector3::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

inline float Vector3::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

inline float& Vector3::At(std::size_t index)
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

inline float Vector3::At(std::size_t index) const
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

constexpr float Vector3::Dot(const Vector3& a, const Vector3& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

constexpr const Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) noexcept
{
    return {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) noexcept
{
    return (a - b).Length();
}

inline float Vector3::Length() const noexcept
{
    return std::sqrtf((x * x) + (y * y) + (z * z));
}

constexpr float Vector3::LengthSq() const noexcept
{
	return (x * x) + (y * y) + (z * z);
}

inline void Vector3::Normalize()
{
    float inverse = 1.0f / std::sqrtf(x*x + y*y + z*z);

	x *= inverse;
	y *= inverse;
	z *= inverse;
}

inline const Vector3 Vector3::Normalized() const
{
    float inverse = 1.0f / std::sqrtf(x*x + y*y + z*z);

    return Vector3(x * inverse, y * inverse, z * inverse);
}

} /* namespace math */
} /* namespace tgon */