#include "PrecompiledHeader.h"

#include <cassert>
#include <cmath>
#include <cstdio>

#include "Vector2.h"

namespace tgon
{

Vector2& Vector2::operator+=(const Vector2& v) noexcept
{
	x += v.x;
	y += v.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) noexcept
{
	x -= v.x;
	y -= v.y;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& v) noexcept
{
	x *= v.x;
	y *= v.y;

	return *this;
}

Vector2& Vector2::operator*=(float scalar) noexcept
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

float& Vector2::operator[](std::size_t index) noexcept
{
    return *(&x + index);
}

float Vector2::operator[](std::size_t index) const noexcept
{
    return *(&x + index);
}

float& Vector2::At(std::size_t index)
{
    assert((index < 2 && index > -1) && "Vector2 index out of range");

    return *(&x + index);
}

float Vector2::At(std::size_t index) const
{
    assert((index < 2 && index > -1) && "Vector2 index out of range");

    return *(&x + index);
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2) noexcept
{
    return Vector2(v1 - v2).Length();
}

float Vector2::Length() const noexcept
{
    return std::sqrtf(this->LengthSq());
}

float Vector2::LengthSq() const noexcept
{
	return (x * x) + (y * y);
}

void Vector2::Normalize()
{
    *this = this->Normalized();
}

const Vector2 Vector2::Normalized() const
{
    float length = this->Length();

    return Vector2(x / length, y / length);
}

template <std::size_t _StrBufferSize>
int32_t Vector2::ToString(char(&destStr)[_StrBufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destStr, "%f %f", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * _StrBufferSize, "%f %f", x, y);
#endif
}

int32_t Vector2::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#endif
}

} /* namespace tgon */