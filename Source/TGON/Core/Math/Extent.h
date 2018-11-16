/**
 * @file    Extent.h
 * @author  ggomdyu
 * @since   04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdio>

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF snprintf
#endif

namespace tgon
{

template <typename _ValueType>
struct BasicExtent2D
{
/**@section Public type */
public:
    using ValueType = _ValueType;

/**@section Public constructor */
public:
    /**@brief   Constructor that initializes members to 0 */
    constexpr BasicExtent2D() noexcept;

    /**@brief   Constructor that initializes the member with the specified value */
    constexpr BasicExtent2D(const _ValueType& width, const _ValueType& height) noexcept;

/**@section Public operator */
public:
    constexpr const BasicExtent2D operator+(const BasicExtent2D& rhs) const noexcept;
    constexpr const BasicExtent2D operator-(const BasicExtent2D& rhs) const noexcept;
    constexpr const BasicExtent2D operator*(const _ValueType& rhs) const noexcept;
    constexpr const BasicExtent2D operator/(const _ValueType& rhs) const;
    constexpr const BasicExtent2D operator-() const noexcept;
    BasicExtent2D& operator+=(const BasicExtent2D& rhs) noexcept;
    BasicExtent2D& operator-=(const BasicExtent2D& rhs) noexcept;
    BasicExtent2D& operator*=(const _ValueType& rhs) noexcept;
    BasicExtent2D& operator/=(const _ValueType& rhs);
    constexpr bool operator==(const BasicExtent2D& rhs) const noexcept;
    constexpr bool operator!=(const BasicExtent2D& rhs) const noexcept;

    template <typename _CastToType>
    constexpr operator BasicExtent2D<_CastToType>() const noexcept;

/**@section Public method */
public:
    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string.
     */
    template <uint32_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The buffer size of destStr.
     * @return  The length of string.
     */
    int32_t ToString(char* destStr, uint32_t strBufferSize) const;

/**@section Public variable */
public:
    _ValueType width;
    _ValueType height;
};

template <typename _ValueType>
constexpr BasicExtent2D<_ValueType> MakeExtent(const _ValueType& width, const _ValueType& height) noexcept
{
    return {width, height};
}

using FExtent2D = BasicExtent2D<float>;
using DExtent2D = BasicExtent2D<double>;
using I32Extent2D = BasicExtent2D<int32_t>;
using I64Extent2D = BasicExtent2D<int64_t>;
using IExtent2D = BasicExtent2D<int>;
using LLExtent2D = BasicExtent2D<long long>;

template <typename _ValueType>
constexpr BasicExtent2D<_ValueType>::BasicExtent2D() noexcept :
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr BasicExtent2D<_ValueType>::BasicExtent2D(const _ValueType& width, const _ValueType& height) noexcept :
    width(width),
    height(height)
{
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator+(const BasicExtent2D& rhs) const noexcept
{
    return BasicExtent2D(*this) += rhs;
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator-(const BasicExtent2D& rhs) const noexcept
{
    return BasicExtent2D(*this) -= rhs;
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicExtent2D(*this) *= rhs;
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicExtent2D(*this) /= rhs;
}

template <typename _ValueType>
constexpr const BasicExtent2D<_ValueType> BasicExtent2D<_ValueType>::operator-() const noexcept
{
	return BasicExtent2D(-width, -height);
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
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _ValueType>
inline BasicExtent2D<_ValueType>& BasicExtent2D<_ValueType>::operator/=(const _ValueType& rhs)
{
    width /= rhs;
    height /= rhs;

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
    return !(*this == rhs);
}

template <typename _ValueType>
template <typename _CastToType>
constexpr BasicExtent2D<_ValueType>::operator BasicExtent2D<_CastToType>() const noexcept
{
    return BasicExtent2D<_CastToType>((_CastToType)width, (_CastToType)height);
}

template <typename _ValueType>
template <uint32_t _StrBufferSize>
inline int32_t BasicExtent2D<_ValueType>::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, sizeof(destStr));
}

template <typename _ValueType>
inline int32_t BasicExtent2D<_ValueType>::ToString(char* destStr, uint32_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d", width, height);
}

template <>
inline int32_t BasicExtent2D<float>::ToString(char* destStr, uint32_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f", width, height);
}

template <>
inline int32_t BasicExtent2D<double>::ToString(char* destStr, uint32_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%lf %lf", width, height);
}

} /* namespace tgon */

#undef TGON_SPRINTF
