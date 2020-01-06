/**
 * @file    Vector4.h
 * @author  ggomdyu
 * @since   05/18/2019
 */

#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF snprintf
#endif

namespace tgon
{

template <typename _ValueType>
struct BasicVector4
{
/**@section Constructor */
public:
    constexpr BasicVector4() noexcept = default;
    constexpr BasicVector4(const _ValueType& scalar) noexcept;
    constexpr BasicVector4(const _ValueType& x, const _ValueType& y, const _ValueType& z, const _ValueType& w) noexcept;
    template <typename _DerivedExpressionType>
    constexpr BasicVector4(const BaseExpression<_DerivedExpressionType>& expression);
    
/**@section Operator */
public:
    constexpr const AddExpression<BasicVector4, BasicVector4> operator+(const BasicVector4& rhs) const noexcept;
    constexpr const SubtractExpression<BasicVector4, BasicVector4> operator-(const BasicVector4& rhs) const noexcept;
    constexpr const BasicVector4 operator+(const _ValueType& rhs) const noexcept;
    constexpr const BasicVector4 operator-(const _ValueType& rhs) const noexcept;
    constexpr const BasicVector4 operator*(const _ValueType& rhs) const noexcept;
    constexpr const BasicVector4 operator/(const _ValueType& rhs) const;
    constexpr const BasicVector4 operator*(const Matrix4x4& rhs) const noexcept;
    constexpr const BasicVector4 operator-() const noexcept;
    friend constexpr const BasicVector4 operator*(const _ValueType& scalar, const BasicVector4& v) noexcept;
    BasicVector4& operator+=(const BasicVector4& rhs) noexcept;
    BasicVector4& operator-=(const BasicVector4& rhs) noexcept;
    BasicVector4& operator*=(const BasicVector4& rhs) noexcept;
    BasicVector4& operator*=(const _ValueType& rhs) noexcept;
    BasicVector4& operator*=(const Matrix4x4& rhs) noexcept;
    BasicVector4& operator/=(const _ValueType& rhs);
    _ValueType& operator[](int32_t index) noexcept;
    _ValueType operator[](int32_t index) const noexcept;
    constexpr bool operator==(const BasicVector4& rhs) const noexcept;
    constexpr bool operator!=(const BasicVector4& rhs) const noexcept;
    constexpr operator Vector3() const noexcept;
    
/**@section Method */
public:
    static constexpr _ValueType Dot(const BasicVector4& v1, const BasicVector4& v2) noexcept;
    constexpr _ValueType Dot(const BasicVector4& v) const noexcept;
    _ValueType& At(int32_t index);
    _ValueType At(int32_t index) const;
    static _ValueType Distance(const BasicVector4& v1, const BasicVector4& v2) noexcept;
    _ValueType Distance(const BasicVector4& v) const noexcept;
    _ValueType Length() const noexcept;
    _ValueType LengthSq() const noexcept;
    void Normalize();
    const BasicVector4 Normalized() const;
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, size_t destStrBufferLen) const;
    std::string ToString() const;

/**@section Variable */
public:
	_ValueType x{}, y{}, z{}, w{};
};
    
using Vector4 = BasicVector4<float>;
using DVector4 = BasicVector4<double>;

template <typename... _Types>
BasicVector4(_Types...) -> BasicVector4<std::common_type_t<_Types...>>;

template <typename _ValueType>
constexpr BasicVector4<_ValueType>::BasicVector4(const _ValueType& scalar) noexcept :
    BasicVector4(scalar, scalar, scalar, scalar)
{
}

template <typename _ValueType>
constexpr BasicVector4<_ValueType>::BasicVector4(const _ValueType& x, const _ValueType& y, const _ValueType& z, const _ValueType& w) noexcept :
    x(x),
    y(y),
    z(z),
    w(w)
{
}

template <typename _ValueType>
template <typename _DerivedExpressionType>
constexpr BasicVector4<_ValueType>::BasicVector4(const BaseExpression<_DerivedExpressionType>& expression) :
    BasicVector4(expression[0], expression[1], expression[2], expression[3])
{
}

template <typename _ValueType>
constexpr const AddExpression<BasicVector4<_ValueType>, BasicVector4<_ValueType>> BasicVector4<_ValueType>::operator+(const BasicVector4& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const SubtractExpression<BasicVector4<_ValueType>, BasicVector4<_ValueType>> BasicVector4<_ValueType>::operator-(const BasicVector4& rhs) const noexcept
{
    return {*this, rhs};
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator+(const _ValueType& rhs) const noexcept
{
    return BasicVector4(x + rhs, y + rhs, z + rhs, w + rhs);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator-(const _ValueType& rhs) const noexcept
{
    return BasicVector4(x - rhs, y - rhs, z - rhs, w - rhs);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicVector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicVector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator*(const Matrix4x4& rhs) const noexcept
{
    return Vector4(
        (x * rhs.m00) + (y * rhs.m10) + (z * rhs.m20) + (w * rhs.m30),
        (x * rhs.m01) + (y * rhs.m11) + (z * rhs.m21) + (w * rhs.m31),
        (x * rhs.m02) + (y * rhs.m12) + (z * rhs.m22) + (w * rhs.m32),
        (x * rhs.m03) + (y * rhs.m13) + (z * rhs.m23) + (w * rhs.m33)
   );
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> BasicVector4<_ValueType>::operator-() const noexcept
{
    return BasicVector4(-x, -y, -z, -w);
}

template <typename _ValueType>
constexpr const BasicVector4<_ValueType> operator*(const _ValueType& scalar, const BasicVector4<_ValueType>& v) noexcept
{
    return v * scalar;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator+=(const BasicVector4& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator-=(const BasicVector4& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator*=(const BasicVector4& rhs) noexcept
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    
    return *this;
}

template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    
    return *this;
}
    
template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator*=(const Matrix4x4& rhs) noexcept
{
    *this = Vector4(
        (x * rhs.m00) + (y * rhs.m10) + (z * rhs.m20) + (w * rhs.m30),
        (x * rhs.m01) + (y * rhs.m11) + (z * rhs.m21) + (w * rhs.m31),
        (x * rhs.m02) + (y * rhs.m12) + (z * rhs.m22) + (w * rhs.m32),
        (x * rhs.m03) + (y * rhs.m13) + (z * rhs.m23) + (w * rhs.m33)
    );
    
    return *this;
}
    
template <typename _ValueType>
inline BasicVector4<_ValueType>& BasicVector4<_ValueType>::operator/=(const _ValueType& rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    
    return *this;
}

template <typename _ValueType>
inline _ValueType& BasicVector4<_ValueType>::operator[](int32_t index) noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::operator[](int32_t index) const noexcept
{
    return *(&x + index);
}

template <typename _ValueType>
constexpr bool BasicVector4<_ValueType>::operator==(const BasicVector4& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}

template <typename _ValueType>
constexpr bool BasicVector4<_ValueType>::operator!=(const BasicVector4& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _ValueType>
inline constexpr BasicVector4<_ValueType>::operator Vector3() const noexcept
{
    return Vector3(x, y, z);
}

template <typename _ValueType>
constexpr _ValueType BasicVector4<_ValueType>::Dot(const BasicVector4& v1, const BasicVector4& v2) noexcept
{
    return v1.Dot(v2);
}
    
template <typename _ValueType>
constexpr _ValueType BasicVector4<_ValueType>::Dot(const BasicVector4& v) const noexcept
{
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

template <typename _ValueType>
inline _ValueType& BasicVector4<_ValueType>::At(int32_t index)
{
    assert((index < 4 && index > -1) && "BasicVector4 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::At(int32_t index) const
{
    assert((index < 4 && index > -1) && "BasicVector4 index out of range");
    
    return *(&x + index);
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::Distance(const BasicVector4& v1, const BasicVector4& v2) noexcept
{
    return BasicVector4(v1 - v2).Length();
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::Distance(const BasicVector4& v) const noexcept
{
    return BasicVector4(*this - v).Length();
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::Length() const noexcept
{
    return std::sqrt(this->LengthSq());
}

template <typename _ValueType>
inline _ValueType BasicVector4<_ValueType>::LengthSq() const noexcept
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

template <typename _ValueType>
inline void BasicVector4<_ValueType>::Normalize()
{
    _ValueType length = this->Length();
    
    x = x / length;
    y = y / length;
    z = z / length;
    w = w / length;
}

template <typename _ValueType>
inline const BasicVector4<_ValueType> BasicVector4<_ValueType>::Normalized() const
{
    _ValueType length = this->Length();
    
    return BasicVector4(x / length, y / length, z / length, w / length);
}

template <typename _ValueType>
inline int32_t BasicVector4<_ValueType>::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <typename _ValueType>
inline int32_t BasicVector4<_ValueType>::ToString(char* destStr, size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f %f %f", x, y, z, w);
}

template <typename _ValueType>
inline std::string BasicVector4<_ValueType>::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

} /* namespace tgon */

#undef TGON_SPRINTF
