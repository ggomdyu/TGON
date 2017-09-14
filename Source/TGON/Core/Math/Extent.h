/**
 * @filename    Extent.h
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
struct BasicExtent2D
{
/* @section Public type */
public:
    using DevideType = typename std::conditional<std::is_floating_point<_ValueType>::value, _ValueType, float>::type;
    using ValueType = _ValueType;

/* @section Public constructor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr BasicExtent2D() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr BasicExtent2D(_ValueType width, _ValueType height) noexcept;

/* @section Public operator */
public:
    constexpr const BasicExtent2D operator+(const BasicExtent2D&) const noexcept;
    constexpr const BasicExtent2D operator-(const BasicExtent2D&) const noexcept;
    constexpr const BasicExtent2D operator*(_ValueType) const noexcept;
    constexpr const BasicExtent2D operator/(DevideType) const;
    constexpr const BasicExtent2D operator+() const noexcept;
    constexpr const BasicExtent2D operator-() const noexcept;
    BasicExtent2D& operator+=(const BasicExtent2D&) noexcept;
    BasicExtent2D& operator-=(const BasicExtent2D&) noexcept;
    BasicExtent2D& operator*=(_ValueType) noexcept;
    BasicExtent2D& operator/=(DevideType);
    constexpr bool operator==(const BasicExtent2D&) const noexcept;
    constexpr bool operator!=(const BasicExtent2D&) const noexcept;

    template <typename _CastToType>
    constexpr operator BasicExtent2D<_CastToType>() const noexcept;

/* @section Public method */
public:
    /**
     * @brief                       Converts to string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @return                      The length of string converted.
     */
    template <std::size_t _BufferSize>
    int32_t ToString(char(&destBuffer)[_BufferSize]) const;

    /**
     * @brief                       Converts to string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @param [in] bufferSize       The size of destBuffer.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destBuffer, std::size_t bufferSize) const;

/* @section Public variable */
public:
    _ValueType width;
    _ValueType height;

    static const BasicExtent2D One;      // 1, 1
    static const BasicExtent2D Zero;     // 0, 0
    static const BasicExtent2D MinusOne; // -1, -1
};

template <typename _ValueType>
constexpr BasicExtent2D<_ValueType> MakeExtent(_ValueType width, _ValueType height) noexcept
{
    return {width, height};
}

using Extent2D = BasicExtent2D<int32_t>;
using FExtent2D = BasicExtent2D<float>;

template<typename _ValueType>
constexpr BasicExtent2D<_ValueType>::BasicExtent2D() noexcept :
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr BasicExtent2D<_ValueType>::BasicExtent2D(_ValueType width, _ValueType height) noexcept :
    width(width),
    height(height)
{
}

template<typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator+(const BasicExtent2D& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator-(const BasicExtent2D& rhs) const noexcept
{
    return TExtent(width - rhs.width, height - rhs.height);
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator/(DevideType rhs) const
{
    return TExtent((_ValueType)((DevideType)width / (DevideType)rhs),
                  (_ValueType)((DevideType)height / (DevideType)rhs));
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator+() const noexcept
{
	return *this;
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator-() const noexcept
{
	return TExtent(-width, -height);
}

template <typename _ValueType>
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator+=(const BasicExtent2D& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename _ValueType>
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator-=(const BasicExtent2D& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename _ValueType>
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator/=(DevideType rhs)
{
    width = (_ValueType)((DevideType)width / rhs);
    height = (_ValueType)((DevideType)height / rhs);

	return *this;
}

template <typename _ValueType>
constexpr bool BasicExtent2D<_ValueType>::operator==(const BasicExtent2D& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename _ValueType>
constexpr bool BasicExtent2D<_ValueType>::operator!=(const BasicExtent2D& rhs) const noexcept
{
    return (width != rhs.width && height != rhs.height);
}

template<typename _ValueType>
template<typename _CastToType>
constexpr BasicExtent2D<_ValueType>::operator BasicExtent2D<_CastToType>() const noexcept
{
    return BasicExtent2D<_CastToType>((_CastToType)width, (_CastToType)height);
}

template <typename _ValueType>
template <std::size_t _BufferSize>
inline int32_t BasicExtent2D<_ValueType>::ToString(char(&destBuffer)[_BufferSize]) const
{
    return this->ToString(destBuffer, _BufferSize);
}

template <typename _ValueType>
inline int32_t BasicExtent2D<_ValueType>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize , "%d %d", width, height);
#endif
}

template <>
inline int32_t BasicExtent2D<float>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%f %f", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%f %f", width, height);
#endif
}

template <>
inline int32_t BasicExtent2D<double>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%lf %lf", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%lf %lf", width, height);
#endif
}

} /* namespace math */
} /* namespace tgon */
