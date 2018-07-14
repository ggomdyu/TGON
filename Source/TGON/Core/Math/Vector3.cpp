#include "PrecompiledHeader.h"

#include <cassert>
#include <cmath>
#include <cstdio>

#include "Vector3.h"

namespace tgon
{

Vector3& Vector3::operator+=(const Vector3& vec) noexcept
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec) noexcept
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec) noexcept
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

Vector3& Vector3::operator*=(float scalar) noexcept
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

float& Vector3::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

float Vector3::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

float& Vector3::At(std::size_t index)
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

float Vector3::At(std::size_t index) const
{
    assert((index < 3 && index > -1) && "Vector3 index out of range");

    return *(&x + index);
}

float Vector3::Distance(const Vector3& v1, const Vector3& v2) noexcept
{
    return Vector3(v1 - v2).Length();
}

float Vector3::Length() const noexcept
{
    return std::sqrtf(this->LengthSq());
}

float Vector3::LengthSq() const noexcept
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3::Normalize()
{
    *this = this->Normalized();
}

const Vector3 Vector3::Normalized() const
{
    float length = this->Length();

    return Vector3(x / length, y / length, z / length);
}

template <std::size_t _StrBufferSize>
int32_t Vector3::ToString(char(&destStr)[_StrBufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destStr, "%f %f %f", x, y, z);
#else
    return snprintf(destStr, sizeof(destStr[0]) * _StrBufferSize, "%f %f %f", x, y, z);
#endif
}

int32_t Vector3::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", x, y, z);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", x, y, z);
#endif
}

} /* namespace tgon */