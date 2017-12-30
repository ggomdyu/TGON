///**
// * @filename    Matrix4x4.h
// * @author      ggomdyu
// * @since       03/14/2016
// */
//
//#pragma once
//
//#include <cstdint>
//#include <cassert>
//#include <cmath>
////#ifdef TGON_SUPPORT_SSE
////#   include <x86intrin.h>
////#endif
//
//#define TGON_ENABLE_EXPRESSION_TEMPLATE
//#define TGON_ENABLE_SIMD
//
//#include "Core/Platform/Config.h"
//
//#include "Vector3.h"
//
//namespace tgon
//{
//namespace math
//{
//
//struct TGON_API Matrix4x4
//{
///* @section Public constructor */
//public:
//    /* @brief   Initializes to Identity matrix. */
//    constexpr Matrix4x4() noexcept;
//
//    /* @brief   Initializes matrix with the specified value. */
//    constexpr Matrix4x4(float m00, float m01, float m02, float m03,
//                        float m10, float m11, float m12, float m13,
//                        float m20, float m21, float m22, float m23,
//                        float m30, float m31, float m32, float m33) noexcept;
//
///* @section Public operator */
//public:
//    Matrix4x4 operator+(const Matrix4x4&) const;
//    Matrix4x4 operator-(const Matrix4x4&) const;
//    Matrix4x4 operator*(const Matrix4x4&) const;
//    Matrix4x4 operator*(float) const;
//    const Matrix4x4& operator+=(const Matrix4x4&);
//    const Matrix4x4& operator-=(const Matrix4x4&);
//    const Matrix4x4& operator*=(const Matrix4x4&);
//    bool operator==(const Matrix4x4& rhs) const;
//    bool operator!=(const Matrix4x4& rhs) const;
//    float* operator[](std::size_t index);
//    const float* operator[](std::size_t index) const;
//
///* @section Public method */
//public:
//    static constexpr const Matrix4x4 Translate(float x, float y, float z) noexcept;
//    static const Matrix4x4 RotateX(float radian);
//    static const Matrix4x4 RotateY(float radian);
//    static const Matrix4x4 RotateZ(float radian);
//    static constexpr const Matrix4x4 Scale(float x, float y, float z) noexcept;
//    static constexpr const Matrix4x4 Transpose(const Matrix4x4& matrix) noexcept;
//    static constexpr const Matrix4x4 Inverse();
//    static Matrix4x4 View(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up);
//    static Matrix4x4 PerspectiveFovLH(float fovY, float aspect, float nearZ, float farZ);
//    static Matrix4x4 PerspectiveFovRH(float fovY, float aspect, float nearZ, float farZ);
//    static Matrix4x4 Viewport(float x, float y, float width, float height, float minZ, float maxZ);
//
///* @section Public variable */
//public:
//    static const Matrix4x4 Zero;
//    static const Matrix4x4 Identity;
//
//    float m00, m01, m02, m03,
//          m10, m11, m12, m13,
//          m20, m21, m22, m23,
//          m30, m31, m32, m33;
//};
//
//constexpr Matrix4x4::Matrix4x4() noexcept :
//    m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
//    m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
//    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
//    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
//{
//}
//
//constexpr Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
//                               float m10, float m11, float m12, float m13,
//                               float m20, float m21, float m22, float m23,
//                               float m30, float m31, float m32, float m33) noexcept :
//    m00(m00), m01(m01), m02(m02), m03(m03),
//    m10(m10), m11(m11), m12(m12), m13(m13),
//    m20(m20), m21(m21), m22(m22), m23(m23),
//    m30(m30), m31(m31), m32(m32), m33(m33)
//{
//}
//
//Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
//{
//    return Matrix4x4(
//        m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02, m03 - rhs.m03,
//        m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
//        m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
//        m30 - rhs.m30, m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33
//    );
//}
//
//Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
//{
//    return Matrix4x4(
//        (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20) + (m03 * rhs.m30),
//        (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21) + (m03 * rhs.m31),
//        (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22) + (m03 * rhs.m32),
//        (m00 * rhs.m03) + (m01 * rhs.m13) + (m02 * rhs.m23) + (m03 * rhs.m33),
//
//        (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20) + (m13 * rhs.m30),
//        (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21) + (m13 * rhs.m31),
//        (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22) + (m13 * rhs.m32),
//        (m10 * rhs.m03) + (m11 * rhs.m13) + (m12 * rhs.m23) + (m13 * rhs.m33),
//
//        (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20) + (m23 * rhs.m30),
//        (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21) + (m23 * rhs.m31),
//        (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22) + (m23 * rhs.m32),
//        (m20 * rhs.m03) + (m21 * rhs.m13) + (m22 * rhs.m23) + (m23 * rhs.m33),
//
//        (m30 * rhs.m00) + (m31 * rhs.m10) + (m32 * rhs.m20) + (m33 * rhs.m30),
//        (m30 * rhs.m01) + (m31 * rhs.m11) + (m32 * rhs.m21) + (m33 * rhs.m31),
//        (m30 * rhs.m02) + (m31 * rhs.m12) + (m32 * rhs.m22) + (m33 * rhs.m32),
//        (m30 * rhs.m03) + (m31 * rhs.m13) + (m32 * rhs.m23) + (m33 * rhs.m33)
//    );
//}
//
//const Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
//{
//    m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
//    m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
//    m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
//    m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;
//
//    return *this;
//}
//
//const Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
//{
//    m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
//    m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
//    m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
//    m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;
//
//    return *this;
//}
//
//Matrix4x4 Matrix4x4::View(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up)
//{
//    Vector3 l = lookAt - eyePt;
//    l.Normalize();
//
//    Vector3 r = Vector3::Cross(up, l);
//    r.Normalize();
//
//    Vector3 u = Vector3::Cross(l, r);
//    u.Normalize();
//
//    return Matrix4x4(
//        r.x, u.x, l.x, 0.f,
//        r.y, u.y, l.y, 0.f,
//        r.z, u.z, l.z, 0.f,
//        -Vector3::Dot(r, eyePt), -Vector3::Dot(u, eyePt), -Vector3::Dot(l, eyePt), 1.f
//    );
//}
//
//Matrix4x4 Matrix4x4::PerspectiveFovLH(float fovY, float aspectRatio, float nearZ, float farZ)
//{
//    float scaleY = 1.0f / std::tan(fovY * 0.5f);
//    float scaleX = scaleY / aspectRatio;
//
//    return Matrix4x4(
//        scaleX, 0.f,    0.f,                                0.f,
//        0.f,    scaleY, 0.f,                                0.f,
//        0.f,    0.f,    farZ / (farZ - nearZ),              1.f,
//        0.f,    0.f,    (-farZ * nearZ) / (farZ - nearZ),   0.f
//    );
//}
//
//inline Matrix4x4 Matrix4x4::PerspectiveFovRH(float fovY, float aspect, float nearZ, float farZ)
//{
//    return Matrix4x4();
//}
//
//Matrix4x4 Matrix4x4::Viewport(float x, float y, float width, float height, float minZ, float maxZ)
//{
//    float halfWidth = width * 0.5f;
//    float halfHeight = height * 0.5f;
//
//    return Matrix4x4(
//        halfWidth,      0.f,            0.f,            0.f,
//        0.f,            -halfHeight,    0.f,            0.f,
//        0.f,            0.f,            maxZ - minZ,    0.f,
//        x + halfWidth,  y + halfHeight, minZ,           1.f
//    );
//}
//
//constexpr const Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& matrix) noexcept
//{
//    return Matrix4x4(
//        matrix.m00, matrix.m10, matrix.m20, matrix.m30,
//        matrix.m01, matrix.m11, matrix.m21, matrix.m31,
//        matrix.m02, matrix.m12, matrix.m22, matrix.m32,
//        matrix.m03, matrix.m13, matrix.m23, matrix.m33
//    );
//}
//
//
////#if TGON_SUPPORT_SSE 1
////inline Matrix4x4::Matrix4x4()
////{
////    _mm_storeu_ps(&m00, _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
////    _mm_storeu_ps(&m10, _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f));
////    _mm_storeu_ps(&m20, _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f));
////    _mm_storeu_ps(&m30, _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f));
////}
////#else
////inline Matrix4x4::Matrix4x4() :
////    m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
////    m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
////    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
////    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
////{
////}
//
//
//inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
//{
//#if TGON_SUPPORT_SSE
//    Matrix4x4 ret;
//
//    _mm_storeu_ps(&ret.m00, _mm_add_ps(_mm_loadu_ps(&m00), _mm_loadu_ps(&rhs.m00)));
//    _mm_storeu_ps(&ret.m10, _mm_add_ps(_mm_loadu_ps(&m10), _mm_loadu_ps(&rhs.m10)));
//    _mm_storeu_ps(&ret.m20, _mm_add_ps(_mm_loadu_ps(&m20), _mm_loadu_ps(&rhs.m20)));
//    _mm_storeu_ps(&ret.m30, _mm_add_ps(_mm_loadu_ps(&m30), _mm_loadu_ps(&rhs.m30)));
//
//    return ret;
//#else
//    return Matrix4x4(
//        m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02, m03 + rhs.m03,
//        m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
//        m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
//        m30 + rhs.m30, m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33
//    );
//#endif
//}
//
//inline const Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
//{
//    *this = (*this)*rhs;
//    return *this;
//}
//
//inline bool Matrix4x4::operator==(const Matrix4x4& rhs) const
//{
//    for (int i = 0; i < 16; ++i)
//    {
//        if ((&(m00))[i] != (&(rhs.m00))[i])
//        {
//            return false;
//        }
//    }
//    return true;
//}
//
//inline float* Matrix4x4::operator[](std::size_t index)
//{
//    assert((index < 4 || index > -1) && "Matrix4x4 index out of range");
//
//    return &m00 + (index * 4);
//}
//
//inline const float* Matrix4x4::operator[](std::size_t index) const
//{
//    assert((index < 4 || index > -1) && "Matrix4x4 index out of range");
//
//    return &m00 + (index * 4);
//}
//
//constexpr const Matrix4x4 Matrix4x4::Translate(float x, float y, float z) noexcept
//{
//    return Matrix4x4(
//        1.f,    0.f,    0.f,    0.f,
//        0.f,    1.f,    0.f,    0.f,
//        0.f,    0.f,    1.f,    0.f,
//        x,      y,      z,      1.f
//    );
//}
//
//inline const Matrix4x4 Matrix4x4::RotateX(float radian)
//{
//    const float cosValue = cosf(radian);
//    const float sinValue = sinf(radian);
//
//    return Matrix4x4(
//        1.f,    0.f,        0.f,        0.f,
//        0.f,    cosValue,   sinValue,   0.f,
//        0.f,    -sinValue,  cosValue,   0.f,
//        0.f,    0.f,        0.f,        1.f
//    );
//}
//
//inline const Matrix4x4 Matrix4x4::RotateY(float theta)
//{
//    const float radCos = cosf(theta);
//    const float radSin = sinf(theta);
//
//    return Matrix4x4(
//        radCos,     0.f,    -radSin,    0.f,
//        0.f,    1.f,    0.f,        0.f,
//        radSin, 0.f,    radCos,     0.f,
//        0.f,    0.f,    0.f,        1.f
//    );
//}
//
//inline const Matrix4x4 Matrix4x4::RotateZ(float theta)
//{
//    const float radCos = cosf(theta);
//    const float radSin = sinf(theta);
//
//    return
//    {
//        radCos,  radSin, 0.f, 0.f,
//        -radSin, radCos, 0.f, 0.f,
//        0.f,     0.f,    1.f, 0.f,
//        0.f,     0.f,    0.f, 1.f
//    };
//}
//
//constexpr const Matrix4x4 Matrix4x4::Scale(float x, float y, float z) noexcept
//{
//    return Matrix4x4(
//        x,      0.f,    0.f,    0.f,
//        0.f,    y,      0.f,    0.f,
//        0.f,    0.f,    z,      0.f,
//        0.f,    0.f,    0.f,    1.f
//    );
//}
//
//} /* namespace math */
//} /* namespace tgon */