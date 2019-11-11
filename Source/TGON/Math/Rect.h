/**
 * @file    Rect.h
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
struct BasicRect
{
/**@section Type */
public:
    using ValueType = _ValueType;

/**@section Constructor */
public:
    /**@brief   Constructor that initializes members to 0 */
    constexpr BasicRect() noexcept;

    /**@brief   Constructor that initializes the member with the specified value */
    constexpr BasicRect(const _ValueType& x, const _ValueType& y, const _ValueType& width, const _ValueType& heght) noexcept;
    
    template <typename _ValueType2>
    constexpr BasicRect(const BasicRect<_ValueType2>& rhs) noexcept;

/**@section Operator */
public:
    constexpr const BasicRect operator+(const BasicRect&) noexcept;
    constexpr const BasicRect operator-(const BasicRect&) noexcept;
    constexpr const BasicRect operator*(const _ValueType&) const noexcept;
    constexpr const BasicRect operator/(const _ValueType&) const;
    constexpr const BasicRect operator-() const noexcept;
    template <typename _ValueType2>
    BasicRect& operator=(const BasicRect<_ValueType2>& rhs) noexcept;
    BasicRect& operator+=(const BasicRect&) noexcept;
    BasicRect& operator-=(const BasicRect&) noexcept;
    BasicRect& operator*=(const _ValueType&) noexcept;
    BasicRect& operator/=(const _ValueType&);
    constexpr bool operator==(const BasicRect&) const noexcept;
    constexpr bool operator!=(const BasicRect&) const noexcept;

/**@section Method */
public:
    constexpr bool Intersect(const BasicRect& rhs) const;

    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string.
     */
    template <std::size_t _DestStrBufferLen>
    int32_t ToString(char(&destStr)[_DestStrBufferLen]) const;

    /**
     * @brief   Creates a string that represents this struct.
     * @param [out] destStr             The destination of the string to be written.
     * @param [in] destStrBufferLen     The buffer size of destStr.
     * @return  The length of string.
     */
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;

/**@section Variable */
public:
    _ValueType x;
    _ValueType y;
    _ValueType width;
    _ValueType height;
};

using FRect = BasicRect<float>;
using DRect = BasicRect<double>;
using I32Rect = BasicRect<int32_t>;
using I64Rect = BasicRect<int64_t>;
using IRect = BasicRect<int>;
using LLRect = BasicRect<long long>;

template <typename... _Types>
BasicRect(_Types...) -> BasicRect<std::common_type_t<_Types...>>;

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect() noexcept :
    x{},
    y{},
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr BasicRect<_ValueType>::BasicRect(const _ValueType& x, const _ValueType& y, const _ValueType& width, const _ValueType& height) noexcept :
    x(x),
    y(y),
    width(width),
    height(height)
{
}

template <typename _ValueType>
template <typename _ValueType2>
constexpr BasicRect<_ValueType>::BasicRect(const BasicRect<_ValueType2>& rhs) noexcept :
    x(static_cast<_ValueType>(rhs.x)),
    y(static_cast<_ValueType>(rhs.y)),
    width(static_cast<_ValueType>(rhs.width)),
    height(static_cast<_ValueType>(rhs.height))
{
}

template <typename _ValueType>
inline constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator+(const BasicRect& rhs) noexcept
{
    return BasicRect(*this) += rhs;
}

template <typename _ValueType>
inline constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-(const BasicRect& rhs) noexcept
{
    return BasicRect(*this) -= rhs;
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator*(const _ValueType& rhs) const noexcept
{
    return BasicRect(*this) *= rhs;
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator/(const _ValueType& rhs) const
{
    return BasicRect(*this) /= rhs;
}

template <typename _ValueType>
constexpr const BasicRect<_ValueType> BasicRect<_ValueType>::operator-() const noexcept
{
    return BasicRect(-x, -y, -width, -height);
}

template <typename _ValueType>
template <typename _ValueType2>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator=(const BasicRect<_ValueType2>& rhs) noexcept
{
    x = static_cast<_ValueType>(rhs.x);
    y = static_cast<_ValueType>(rhs.y);
    width = static_cast<_ValueType>(rhs.width);
    height = static_cast<_ValueType>(rhs.height);
    
    return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator+=(const BasicRect& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    width += rhs.width;
    height += rhs.height;

    return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator-=(const BasicRect& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;
    width -= rhs.width;
    height -= rhs.height;

    return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator*=(const _ValueType& rhs) noexcept
{
    x *= rhs;
    y *= rhs;
    width *= rhs;
    height *= rhs;

    return *this;
}

template <typename _ValueType>
inline BasicRect<_ValueType>& BasicRect<_ValueType>::operator/=(const _ValueType& rhs)
{
    x /= rhs;
    y /= rhs;
    width /= rhs;
    height /= rhs;

    return *this;
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator==(const BasicRect& rhs) const noexcept
{
    return (x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height);
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::operator!=(const BasicRect& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename _ValueType>
constexpr bool BasicRect<_ValueType>::Intersect(const BasicRect& rhs) const
{
    return (x <= rhs.width && y <= rhs.height && width >= rhs.x && height >= rhs.y);
}

template <typename _ValueType>
template <std::size_t _DestStrBufferLen>
inline int32_t BasicRect<_ValueType>::ToString(char(&destStr)[_DestStrBufferLen]) const
{
    return this->ToString(destStr, sizeof(destStr));
}

template <typename _ValueType>
inline int32_t BasicRect<_ValueType>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%d %d %d %d", x, y, width, height);
}

template <>
inline int32_t BasicRect<float>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f %f %f", x, y, width, height);
}

template <>
inline int32_t BasicRect<double>::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%lf %lf %lf %lf", x, y, width, height);
}

} /* namespace tgon */

#undef TGON_SPRINTF
