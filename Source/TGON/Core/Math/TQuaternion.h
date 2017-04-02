/**
 * filename Quaternion.h
 * author   ggomdyu
 * since    03/14/2016
 */

#pragma once
#include "../Platform/TConfig.h"

#include "../Math/TVector3.h"

namespace tgon
{

struct TGON_API TQuaternion
{
/**
 * @section Ctor/Dtor
 */
public:
    TQuaternion();

    // In Quaternion, x, y, z means a Axis. w is angle scalar.
    TQuaternion(float x, float y, float z, float w);

    // Pass axis as Vector3. w is angle scalar.
    TQuaternion(const TVector3& v, float w);

    TQuaternion(const TQuaternion&);

/**
 * @section Operators
 */
public:
    TQuaternion operator*(const TQuaternion&) const;
    TQuaternion operator+() const;
    TQuaternion operator-() const;
    TQuaternion& operator*=(const TQuaternion&);
    bool operator==(const TQuaternion&) const;
    bool operator!=(const TQuaternion&) const;
    float& operator[](std::size_t);
    float operator[](std::size_t) const;
	
/**
 * @section Public methods
 */
public:
    struct TMatrix4x4 RotateMatrix() const;

/**
 * @section Public variables
 */
public:
	float x, y, z, w;

    static const TQuaternion Zero;
    static const TQuaternion Identity;
};

inline TQuaternion::TQuaternion() :
    x(0.f),
    y(0.f),
    z(0.f),
    w(0.f)
{
}

inline TQuaternion::TQuaternion(float x, float y, float z, float w) :
    x(x),
    y(y),
    z(z),
    w(w)
{
}

inline TQuaternion::TQuaternion(const TQuaternion& rhs) :
    x(rhs.x),
    y(rhs.y),
    z(rhs.z),
    w(rhs.w)
{
}

inline TQuaternion TQuaternion::operator*(const TQuaternion& rhs) const
{
    return TQuaternion(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
}

inline TQuaternion TQuaternion::operator+() const
{
    return *this;
}

inline TQuaternion TQuaternion::operator-() const
{
    return TQuaternion(-x, -y, -z, -w);
}

inline TQuaternion& TQuaternion::operator*=(const TQuaternion& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

inline bool TQuaternion::operator==(const TQuaternion& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}

inline bool TQuaternion::operator!=(const TQuaternion& rhs) const
{
    return !(this->operator==(rhs));
}

inline float& TQuaternion::operator[](std::size_t index)
{
    assert((index < 4 && index > -1) && "TQuaternion index out of range");
    return *(&x + index);
}

inline float TQuaternion::operator[](std::size_t index) const
{
    assert((index < 4 && index > -1) && "TQuaternion index out of range");
    return *(&x + index);
}

} /* namespace tgon */
