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
namespace math
{

template <typename _ValueType>
struct BasicRect
{
/* @section Public type */
public:
    using DevideType = typename std::conditional<std::is_floating_point<_ValueType>::value, _ValueType, float>::type;
    using ValueType = _ValueType;

/* @section Public constructor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr BasicRect() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr BasicRect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept;

/* @section Public operator */
public:
    constexpr const BasicRect operator+(const BasicRect&) const noexcept;
    constexpr const BasicRect operator-(const BasicRect&) const noexcept;
    constexpr const BasicRect operator*(_ValueType) const noexcept;
    constexpr const BasicRect operator/(DevideType) const;
    constexpr const BasicRect operator+() const noexcept;
    constexpr const BasicRect operator-() const noexcept;
    BasicRect& operator+=(const BasicRect&) noexcept;
    BasicRect& operator-=(const BasicRect&) noexcept;
    BasicRect& operator*=(_ValueType) noexcept;
    BasicRect& operator/=(DevideType);
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

	static const BasicRect One;		// 0, 0, 0, 0
	static const BasicRect Zero;	    // 1, 1, 1, 1
	static const BasicRect MinusOne;	// -1, -1, -1, -1
};

template <typename _ValueType>
constexpr BasicRect<_ValueType> MakeRect(_ValueType left, _ValueType top, _ValueType right, _ValueType bottom) noexcept
{
    return {left, top, right, bottom};
}

using Rect = BasicRect<int32_t>;
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
constexpr BasicRect<_ValueType>::BasicRect(_ValueType left, _ValueType top, _ValueType right, _ValueType bottom) noexcept :
    left(left),
    top(top),
    right(right),
    bottom(bottom)
{
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator+(const BasicRect& rhs) const noexcept
{
    return BasicRect(left + rhs.left, top + rhs.top, right + rhs.right, bottom + rhs.bottom);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-(const BasicRect& rhs) const noexcept
{
    return BasicRect(left + rhs.left, top - rhs.top, right - rhs.right, bottom - rhs.bottom);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return BasicRect(left * rhs, top * rhs, right * rhs, bottom * rhs);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator/(DevideType rhs) const
{
    DevideType inverse = 1.0f / rhs;

    return BasicRect((_ValueType)((DevideType)left * inverse),
                     (_ValueType)((DevideType)top * inverse),
                     (_ValueType)((DevideType)right * inverse),
                     (_ValueType)((DevideType)bottom * inverse));
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator+() const noexcept
{
	return *this;
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
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    left *= rhs;
    top *= rhs;
    right *= rhs;
    bottom *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator/=(DevideType rhs)
{
	DevideType inverse = 1.0f / rhs;

    left = (_ValueType)((DevideType)left * inverse);
    top = (_ValueType)((DevideType)top * inverse);
    right = (_ValueType)((DevideType)right * inverse);
    bottom = (_ValueType)((DevideType)bottom * inverse);

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

} /* namespace math */
} /* namespace tgon */
