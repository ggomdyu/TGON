/**
 * @file    Extent.h
 * @author  ggomdyu
 * @since   04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdio>
#include <string>
#include <gsl/span>

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
/**@section Type */
public:
    using ValueType = _ValueType;

/**@section Constructor */
public:
    constexpr BasicExtent2D() noexcept = default;
    constexpr BasicExtent2D(const _ValueType& width, const _ValueType& height) noexcept;

/**@section Operator */
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

/**@section Method */
public:
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    std::string ToString() const;

/**@section Variable */
public:
    _ValueType width{}, height{};
};

using FExtent2D = BasicExtent2D<float>;
using DExtent2D = BasicExtent2D<double>;
using I32Extent2D = BasicExtent2D<int32_t>;
using I64Extent2D = BasicExtent2D<int64_t>;
using IExtent2D = BasicExtent2D<int>;
using LLExtent2D = BasicExtent2D<long long>;

template <typename... _Types>
BasicExtent2D(_Types...) -> BasicExtent2D<std::common_type_t<_Types...>>;

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
inline int32_t BasicExtent2D<_ValueType>::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

template <typename _ValueType>
inline std::string BasicExtent2D<_ValueType>::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

template <typename _ValueType>
inline int32_t BasicExtent2D<_ValueType>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%d %d", width, height);
}

template <>
inline int32_t BasicExtent2D<float>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f", width, height);
}

template <>
inline int32_t BasicExtent2D<double>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%lf %lf", width, height);
}

} /* namespace tgon */

#undef TGON_SPRINTF
