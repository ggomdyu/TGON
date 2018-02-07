/**
 * @filename    Rect.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdio>

namespace tgon
{
namespace core
{

template <typename _ValueType>
struct BasicRect
{
/* @section Public type */
public:
    using ValueType = _ValueType;

/* @section Public constructor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr BasicRect() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr BasicRect(const _ValueType& left, const _ValueType& top, const _ValueType& right, const _ValueType& bottom) noexcept;

/* @section Public operator */
public:
    constexpr const BasicRect operator*(const _ValueType&) const noexcept;
    constexpr const BasicRect operator/(const _ValueType&) const;
    constexpr const BasicRect operator-() const noexcept;
    BasicRect& operator+=(const BasicRect&) noexcept;
    BasicRect& operator-=(const BasicRect&) noexcept;
    BasicRect& operator*=(const _ValueType&) noexcept;
    BasicRect& operator/=(const _ValueType&);
    constexpr bool operator==(const BasicRect&) const noexcept;
    constexpr bool operator!=(const BasicRect&) const noexcept;

/* @section Public method */
public:
    constexpr bool Intersect(const BasicRect& rhs) const;

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
     * @param [in] strBufferSize    The size of destStr.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/* @section Public variable */
public:
    _ValueType left;
    _ValueType top;
    _ValueType right;
    _ValueType bottom;
};

template <typename _ValueType>
constexpr BasicRect<_ValueType> MakeRect(const _ValueType& left, const _ValueType& top, const _ValueType& right, const _ValueType& bottom) noexcept
{
    return {left, top, right, bottom};
}

using Rect = BasicRect<int>;
using I32Rect = BasicRect<int32_t>;
using I64Rect = BasicRect<int64_t>;
using FRect = BasicRect<float>;

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect() noexcept :
    left{},
    top{},
    right{},
    bottom{}
{
}

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect(const _ValueType& left, const _ValueType& top, const _ValueType& right, const _ValueType& bottom) noexcept :
    left(left),
    top(top),
    right(right),
    bottom(bottom)
{
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicRect(left * rhs, top * rhs, right * rhs, bottom * rhs);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicRect(left / rhs, top / rhs, right / rhs, bottom / rhs);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-() const noexcept
{
	return BasicRect(-left, -top, -right, -bottom);
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator+=(const BasicRect& rhs) noexcept
{
	left += rhs.left;
    top += rhs.top;
	right += rhs.right;
    bottom += rhs.bottom;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator-=(const BasicRect& rhs) noexcept
{
    left -= rhs.left;
    top -= rhs.top;
    right -= rhs.right;
    bottom -= rhs.bottom;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    left *= rhs;
    top *= rhs;
    right *= rhs;
    bottom *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator/=(const _ValueType& rhs)
{
    left /= rhs;
    top /= rhs;
    right /= rhs;
    bottom /= rhs;

	return *this;
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator==(const BasicRect& rhs) const noexcept
{
	return (left == rhs.left && top == rhs.top && right == rhs.right && bottom == rhs.bottom);
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator!=(const BasicRect& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::Intersect(const BasicRect& rhs) const
{
    return (left <= rhs.right && top <= rhs.bottom && right >= left && bottom >= rhs.top);
}

template <typename _ValueType>
template <std::size_t _StrBufferSize>
inline int32_t BasicRect<_ValueType>::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

template <typename _ValueType>
inline int32_t BasicRect<_ValueType>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", left, top, right, bottom);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", left, top, right, bottom);
#endif
}

template <>
inline int32_t BasicRect<float>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", left, top, right, bottom);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", left, top, right, bottom);
#endif
}

template <>
inline int32_t BasicRect<double>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf %lf %lf", left, top, right, bottom);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf %lf %lf", left, top, right, bottom);
#endif
}

} /* namespace core */
} /* namespace tgon */
