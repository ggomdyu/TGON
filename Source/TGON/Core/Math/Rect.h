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
    /**
     * @brief                   Converts value to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return                  The length of string converted.
     */
    template <std::size_t _BufferSize>
    int32_t ToString(char(&destStr)[_BufferSize]) const;

    /**
     * @brief                       Converts value to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/* @section Public variable */
public:
    _ValueType bottom;
    _ValueType top;
    _ValueType width;
    _ValueType height;

	static const BasicRect One;		// 0, 0, 0, 0
	static const BasicRect Zero;	    // 1, 1, 1, 1
	static const BasicRect MinusOne;	// -1, -1, -1, -1
};

template <typename _ValueType>
constexpr BasicRect<_ValueType> MakeRect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept
{
    return {bottom, top, width, height};
}

using Rect = BasicRect<int32_t>;
using FRect = BasicRect<float>;

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect() noexcept :
    bottom{},
    top{},
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept :
    bottom( bottom),
    top(top),
    width(width),
    height(height)
{
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator+(const BasicRect& rhs) const noexcept
{
    return BasicRect(bottom + rhs.bottom, top + rhs.top, width + rhs.width, height + rhs.height);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-(const BasicRect& rhs) const noexcept
{
    return BasicRect(bottom - rhs.bottom, top - rhs.top, width - rhs.width, height - rhs.height);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return BasicRect(bottom * rhs, top * rhs, width * rhs, height * rhs);
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator/(DevideType rhs) const
{
    DevideType inverse = 1.0f / rhs;

    return BasicRect((_ValueType)((DevideType)bottom * inverse),
                     (_ValueType)((DevideType)top * inverse),
                     (_ValueType)((DevideType)width * inverse),
                     (_ValueType)((DevideType)height * inverse));
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator+() const noexcept
{
	return *this;
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-() const noexcept
{
	return BasicRect(-bottom, -top, -width, -height);
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator+=(const BasicRect& rhs) noexcept
{
	bottom += rhs.bottom;
    top += rhs.top;
	width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator-=(const BasicRect& rhs) noexcept
{
    bottom -= rhs.bottom;
    top -= rhs.top;
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    bottom *= rhs;
    top *= rhs;
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator/=(DevideType rhs)
{
	DevideType inverse = 1.0f / rhs;

    bottom = (_ValueType)((DevideType)bottom * inverse);
    top = (_ValueType)((DevideType)top * inverse);
    width = (_ValueType)((DevideType)width * inverse);
    height = (_ValueType)((DevideType)height * inverse);

	return *this;
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator==(const BasicRect& rhs) const noexcept
{
	return (bottom == rhs.bottom && top == rhs.top && width == rhs.width && height == rhs.height);
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator!=(const BasicRect& rhs) const noexcept
{
    return (bottom != rhs.bottom || top != rhs.top || width != rhs.width || height != rhs.height);
}

template <typename _ValueType>
template <std::size_t _BufferSize>
inline int32_t BasicRect<_ValueType>::ToString(char(&destStr)[_BufferSize]) const
{
    return this->ToString(destStr, _BufferSize);
}

template <typename _ValueType>
inline int32_t BasicRect<_ValueType>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize , "%d %d %d %d", bottom, top, width, height);
#endif
}

template <>
inline int32_t BasicRect<float>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", bottom, top, width, height);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize , "%f %f %f %f", bottom, top, width, height);
#endif
}

template <>
inline int32_t BasicRect<double>::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf %lf %lf", bottom, top, width, height);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf %lf %lf", bottom, top, width, height);
#endif
}

} /* namespace math */
} /* namespace tgon */
