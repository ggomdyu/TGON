/**
 * @filename    Extent.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <string>

namespace tgon
{
namespace math
{

template <typename _ValueType>
struct Extent2D
{
public:
    using DevideType = typename std::conditional<std::is_floating_point<_ValueType>::value, _ValueType, float>::type;
    using ValueType = _ValueType;

/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Extent2D() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Extent2D(_ValueType width, _ValueType height) noexcept;

/* @section Operator */
public:
    constexpr const Extent2D operator+(const Extent2D&) const noexcept;
    constexpr const Extent2D operator-(const Extent2D&) const noexcept;
    constexpr const Extent2D operator*(_ValueType) const noexcept;
    constexpr const Extent2D operator/(DevideType) const;
    constexpr const Extent2D operator+() const noexcept;
    constexpr const Extent2D operator-() const noexcept;
    Extent2D& operator+=(const Extent2D&) noexcept;
    Extent2D& operator-=(const Extent2D&) noexcept;
    Extent2D& operator*=(_ValueType) noexcept;
    Extent2D& operator/=(DevideType);
    constexpr bool operator==(const Extent2D&) const noexcept;
    constexpr bool operator!=(const Extent2D&) const noexcept;

    template <typename _CastToType>
    constexpr operator Extent2D<_CastToType>() const noexcept;

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

    /* @brief                       Converts to string. */
    std::string ToString() const;

/* @section Public variable */
public:
    _ValueType width;
    _ValueType height;

	static const Extent2D One;		// 1, 1
	static const Extent2D Zero;	    // 0, 0
	static const Extent2D MinusOne;	// -1, -1
};

template <typename _ValueType>
constexpr Extent2D<_ValueType> MakeExtent(_ValueType width, _ValueType height) noexcept
{
    return {width, height};
}

using IntExtent2D = Extent2D<int32_t>;
using FloatExtent2D = Extent2D<float>;

template<typename _ValueType>
constexpr Extent2D<_ValueType>::Extent2D() noexcept :
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr Extent2D<_ValueType>::Extent2D(_ValueType width, _ValueType height) noexcept :
    width(width),
    height(height)
{
}

template<typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator+(const Extent2D& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator-(const Extent2D& rhs) const noexcept
{
    return TExtent(width - rhs.width, height - rhs.height);
}

template <typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator/(DevideType rhs) const
{
    return TExtent((_ValueType)((DevideType)width / (DevideType)rhs),
                  (_ValueType)((DevideType)height / (DevideType)rhs));
}

template <typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator+() const noexcept
{
	return *this;
}

template <typename _ValueType>
constexpr const Extent2D<_ValueType> Extent2D<_ValueType>::operator-() const noexcept
{
	return TExtent(-width, -height);
}

template <typename _ValueType>
inline Extent2D<_ValueType>& Extent2D<_ValueType>::operator+=(const Extent2D& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename _ValueType>
inline Extent2D<_ValueType>& Extent2D<_ValueType>::operator-=(const Extent2D& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename _ValueType>
inline Extent2D<_ValueType>& Extent2D<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _ValueType>
inline Extent2D<_ValueType>& Extent2D<_ValueType>::operator/=(DevideType rhs)
{
    width = (_ValueType)((DevideType)width / rhs);
    height = (_ValueType)((DevideType)height / rhs);

	return *this;
}

template <typename _ValueType>
inline constexpr bool Extent2D<_ValueType>::operator==(const Extent2D& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename _ValueType>
inline constexpr bool Extent2D<_ValueType>::operator!=(const Extent2D& rhs) const noexcept
{
    return (width != rhs.width && height != rhs.height);
}

template<typename _ValueType>
template<typename _CastToType>
constexpr Extent2D<_ValueType>::operator Extent2D<_CastToType>() const noexcept
{
    return Extent2D<_CastToType>((_CastToType)width, (_CastToType)height);
}

template<typename _ValueType>
template<std::size_t _BufferSize>
inline int32_t Extent2D<_ValueType>::ToString(char(&destBuffer)[_BufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * _BufferSize, "%d %d", width, height);
#endif
}

template<typename _ValueType>
inline int32_t Extent2D<_ValueType>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#endif
}

template<typename _ValueType>
inline std::string Extent2D<_ValueType>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
