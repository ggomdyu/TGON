/**
 * @filename    TVector3.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {
namespace math {

struct TGON_API TVector3
{
/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr TVector3() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr TVector3(float x, float y, float z) noexcept;

/**
 * @section Operator
 */
public:
    const TVector3 operator+(const TVector3&) const noexcept;
    const TVector3 operator-(const TVector3&) const noexcept;
    const TVector3 operator*(const TVector3&) const noexcept;
    friend const TVector3 operator*(float, const TVector3& rhs) noexcept;
    const TVector3 operator*(float) const noexcept;
    const TVector3 operator/(float) const;
    const TVector3 operator+() const noexcept;
    const TVector3 operator-() const noexcept;
    TVector3& operator+=(const TVector3&) noexcept;
    TVector3& operator-=(const TVector3&) noexcept;
    TVector3& operator*=(const TVector3&) noexcept;
    TVector3& operator*=(float) noexcept;
    TVector3& operator/=(float);
    constexpr bool operator==(const TVector3&) const noexcept;
    constexpr bool operator!=(const TVector3&) const noexcept;
    float& operator[](std::size_t) noexcept;
    float operator[](std::size_t) const noexcept;
	
/**
 * @section Public command method
 */
public:
    static constexpr float Dot(const TVector3& a, const TVector3& b) noexcept;
    static constexpr TVector3 Cross(const TVector3& a, const TVector3& b) noexcept;
    static float Angle(const TVector3& a, const TVector3& b) noexcept;
    static float Distance(const TVector3& a, const TVector3& b) noexcept;
    float& At(std::size_t index);
    float At(std::size_t index) const;
    float Length() const noexcept;
    constexpr float LengthSq() const noexcept;
    void Normalize();
    const TVector3 Normalized() const;
    void TransformCoord(const struct TMatrix4x4&) noexcept;
    void TransformNormal(const struct TMatrix4x4&) noexcept;

/**
 * @section Public variables
 */
public:
	float x, y, z;

    static const TVector3 Forward;	// 0, 0, 1
	static const TVector3 Back;		// 0, 0, -1
	static const TVector3 Up;		// 0, 1, 0
	static const TVector3 Down;		// 0, -1, 0
	static const TVector3 Left;		// -1, 0, 0
	static const TVector3 Right;	// 1, 0, 0
	static const TVector3 One;		// 0, 0, 0
	static const TVector3 Zero;		// 1, 1, 1
};

constexpr TVector3::TVector3() noexcept :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

constexpr TVector3::TVector3(float x, float y, float z) noexcept :
    x(x),
	y(y), 
	z(z)
{
}

inline const TVector3 TVector3::operator+(const TVector3& rhs) const noexcept
{
    return TVector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline const TVector3 TVector3::operator-(const TVector3& rhs) const noexcept
{
    return TVector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline const TVector3 TVector3::operator*(const TVector3& rhs) const noexcept
{
    return TVector3(x*rhs.x, y*rhs.y, z*rhs.z);
}

inline const TVector3 TVector3::operator*(float rhs) const noexcept
{
    return TVector3(x*rhs, y*rhs, z*rhs);
}

inline const TVector3 operator*(float lhs, const TVector3& rhs) noexcept
{
	return rhs * lhs;
}

inline const TVector3 TVector3::operator/(float value) const
{
    assert(value != 0.0f && "Vector elements can't be divided by zero.");

	const float inverse = 1.0f / value;
    return TVector3(x * inverse, y * inverse, z * inverse);
}

inline const TVector3 TVector3::operator+() const noexcept
{
	return *this;
}

inline const TVector3 TVector3::operator-() const noexcept
{
	return TVector3(-x, -y, -z);
}

inline TVector3& TVector3::operator+=(const TVector3& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline TVector3& TVector3::operator-=(const TVector3& rhs) noexcept
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline TVector3& TVector3::operator*=(const TVector3& rhs) noexcept
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

inline TVector3& TVector3::operator*=(float rhs) noexcept
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

inline TVector3& TVector3::operator/=(float value)
{
	const float inverse = 1.0f / value;

	x *= inverse;
	y *= inverse;
	z *= inverse;

	return *this;
}

inline constexpr bool TVector3::operator==(const TVector3& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

inline constexpr bool TVector3::operator!=(const TVector3& rhs) const noexcept
{
    return (x != rhs.x || y != rhs.y || z != rhs.z);
}

inline float& TVector3::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

inline float TVector3::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

inline float& TVector3::At(std::size_t index)
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

inline float TVector3::At(std::size_t index) const
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

constexpr float TVector3::Dot(const TVector3& a, const TVector3& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

constexpr TVector3 TVector3::Cross(const TVector3& a, const TVector3& b) noexcept
{
    return {(a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)};
}

inline float TVector3::Distance(const TVector3& a, const TVector3& b) noexcept
{
    return (a - b).Length();
}

inline float TVector3::Length() const noexcept
{
    return std::sqrtf((x * x) + (y * y) + (z * z));
}

constexpr float TVector3::LengthSq() const noexcept
{
	return (x * x) + (y * y) + (z * z);
}

inline void TVector3::Normalize()
{
    const float inverse = 1.0f / std::sqrtf(x*x + y*y + z*z);

	x *= inverse;
	y *= inverse;
	z *= inverse;
}

inline const TVector3 TVector3::Normalized() const
{
    const float inverse = 1.0f / std::sqrtf(x*x + y*y + z*z);

    return TVector3(x * inverse, y * inverse, z * inverse);
}

} /* namespace math */
} /* namespace tgon */