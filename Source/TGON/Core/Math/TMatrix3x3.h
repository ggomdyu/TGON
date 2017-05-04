/**
 * @filename    TMatrix3x3.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "../Platform/TConfig.h"

namespace tgon {
namespace math {

struct TGON_API TMatrix3x3
{
public:
    TMatrix3x3();
    TMatrix3x3(float _00, float _01, float _02,
               float _10, float _11, float _12,
               float _20, float _21, float _22);
	
    TMatrix3x3 operator+(const TMatrix3x3&) const;
    TMatrix3x3 operator-(const TMatrix3x3&) const;
    TMatrix3x3 operator*(const TMatrix3x3&) const;
    TMatrix3x3 operator*(float) const;
    TMatrix3x3 operator+() const;
    TMatrix3x3 operator-() const;
    const TMatrix3x3& operator+=(const TMatrix3x3&);
    const TMatrix3x3& operator-=(const TMatrix3x3&);
    const TMatrix3x3& operator*=(const TMatrix3x3&);
    bool operator==(const TMatrix3x3&) const;
    bool operator!=(const TMatrix3x3&) const;
    float* operator[](std::size_t row);
    const float* operator[](std::size_t row) const;
	
public:
    static TMatrix3x3 Scale(float x, float y, float z);
    static TMatrix3x3 RotateX(float theta);
    static TMatrix3x3 RotateY(float theta);
    static TMatrix3x3 RotateZ(float theta);

    void Transpose();
    void Inverse();

public:
	float _00, _01, _02,
		  _10, _11, _12,
		  _20, _21, _22;
	
    static const TMatrix3x3 Identity;
	static const TMatrix3x3 Zero;
};

inline const TMatrix3x3& TMatrix3x3::operator*=(const TMatrix3x3& rhs)
{
    *this = (*this)*rhs;
    return *this;
}

inline float* TMatrix3x3::operator[](std::size_t row)
{
    assert((row < 3 && row > -1) && "TMatrix3x3 index out of range");

    return (&_00 + row * 3);
}

inline const float* TMatrix3x3::operator[](std::size_t row) const
{
    assert((row < 3 && row > -1) && "TMatrix3x3 index out of range");

    return (&_00 + row * 3);
}

inline TMatrix3x3 TMatrix3x3::RotateX(float theta)
{
    const float radCos = cosf(theta);
    const float radSin = sinf(theta);

    return{
        1.f, 0.f,     0.f,
        0.f, radCos,  radSin,
        0.f, -radSin, radCos,
    };
}

inline TMatrix3x3 TMatrix3x3::RotateY(float theta)
{
    const float radCos = cosf(theta);
    const float radSin = sinf(theta);

    return{
        radCos, 0.f, -radSin,
        0.f,    1.f, 0.f,
        radSin, 0.f, radCos,
    };
}

inline TMatrix3x3 TMatrix3x3::RotateZ(float theta)
{
    const float radCos = cosf(theta);
    const float radSin = sinf(theta);

    return{
        radCos,  radSin, 0.f,
        -radSin, radCos, 0.f,
        0.f,     0.f,    1.f,
    };
}

inline TMatrix3x3 TMatrix3x3::Scale(float x, float y, float z)
{
    return{
        x,   0.f, 0.f,
        0.f, y,	  0.f,
        0.f, 0.f, z,
    };
}

} /* namespace math */
} /* namespace tgon */