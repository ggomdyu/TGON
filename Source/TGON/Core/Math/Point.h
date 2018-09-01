/**
 * @file    Point.h
 * @author  ggomdyu
 * @since   04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdio>

namespace tgon
{

template <typename _ValueType>
struct BasicPoint
{
/* @section Public type */
public:
    using ValueType = _ValueType;

/* @section Public constructor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr BasicPoint() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr BasicPoint(const _ValueType& x, const _ValueType& y) noexcept;

/* @section Public operator */
public:
    constexpr const BasicPoint operator+(const BasicPoint&) const noexcept;
    constexpr const BasicPoint operator-(const BasicPoint&) const noexcept;
    constexpr const BasicPoint operator*(const _ValueType&) const noexcept;
    constexpr const BasicPoint operator/(const _ValueType&) const;
    constexpr const BasicPoint operator-() const noexcept;
    BasicPoint& operator+=(const BasicPoint&) noexcept;
    BasicPoint& operator-=(const BasicPoint&) noexcept;
    BasicPoint& operator*=(const _ValueType&) noexcept;
    BasicPoint& operator/=(const _ValueType&);
    constexpr bool operator==(const BasicPoint&) const noexcept;
    constexpr bool operator!=(const BasicPoint&) const noexcept;

    template <typename _CastToType>
    constexpr operator BasicPoint<_CastToType>() const noexcept;

/* @section Public method */
public:
    /**
     * @brief   Converts value to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Converts value to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/* @section Public variable */
public:
    _ValueType x;
    _ValueType y;
};

using Point = BasicPoint<float>;
using DPoint = BasicPoint<double>;
using I64Point = BasicPoint<int64_t>;
using I32Point = BasicPoint<int32_t>;
using IPoint = BasicPoint<int>;
using LLPoint = BasicPoint<long long>;

template <typename _ValueType>
constexpr BasicPoint<_ValueType> MakePoint(const _ValueType& x, const _ValueType& y) noexcept
{
    return {x, y};
}

template <typename _ValueType>
constexpr BasicPoint<_ValueType>::BasicPoint() noexcept :
    x{},
    y{}
{
}

template <typename _ValueType>
constexpr BasicPoint<_ValueType>::BasicPoint(const _ValueType& x, const _ValueType& y) noexcept :
    x(x),
    y(y)
{
}

template <typename _ValueType>
constexpr const BasicPoint<_ValueType> BasicPoint<_ValueType>::operator+(const BasicPoint& rhs) const noexcept
{
    return BasicPoint(*this) += rhs;
}

template <typename _ValueType>
constexpr const BasicPoint<_ValueType> BasicPoint<_ValueType>::operator-(const BasicPoint& rhs) const noexcept
{
    return BasicPoint(*this) -= rhs;
}

template <typename _ValueType>
constexpr const BasicPoint<_ValueType> BasicPoint<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicPoint(*this) *= rhs;
}

template <typename _ValueType>
constexpr const BasicPoint<_ValueType> BasicPoint<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicPoint(*this) /= rhs;
}

template <typename _ValueType>
constexpr const BasicPoint<_ValueType> BasicPoint<_ValueType>::operator-() const noexcept
{
	return BasicPoint(-x, -y);
}

template <typename _ValueType>
inline BasicPoint<_ValueType>& BasicPoint<_ValueType>::operator+=(const BasicPoint& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;

	return *this;
}

template <typename _ValueType>
inline BasicPoint<_ValueType>& BasicPoint<_ValueType>::operator-=(const BasicPoint& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;

	return *this;
}

template <typename _ValueType>
inline BasicPoint<_ValueType>& BasicPoint<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    x *= rhs;
    y *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicPoint<_ValueType>& BasicPoint<_ValueType>::operator/=(const _ValueType& rhs)
{
    x /= rhs;
    y /= rhs;

	return *this;
}

template <typename _ValueType>
constexpr bool BasicPoint<_ValueType>::operator==(const BasicPoint& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y);
}

template <typename _ValueType>
constexpr bool BasicPoint<_ValueType>::operator!=(const BasicPoint& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _ValueType>
template <typename _CastToType>
constexpr BasicPoint<_ValueType>::operator BasicPoint<_CastToType>() const noexcept
{
    return BasicPoint<_CastToType>(static_cast<_CastToType>(x), static_cast<_CastToType>(y));
}

template <typename _ValueType>
template <std::size_t _StrBufferSize>
inline int32_t BasicPoint<_ValueType>::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

template <typename _ValueType>
inline int32_t BasicPoint<_ValueType>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d", x, y);
#endif
}

template <>
inline int32_t BasicPoint<float>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", x, y);
#endif
}

template <>
inline int32_t BasicPoint<double>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf", x, y);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf", x, y);
#endif
}

} /* namespace tgon */
