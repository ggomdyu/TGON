/**
 * @filename    Rect.h
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
struct Rect
{
/* @section Public type */
public:
    using DevideType = typename std::conditional<std::is_floating_point<_ValueType>::value, _ValueType, float>::type;
    using ValueType = _ValueType;

/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Rect() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Rect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept;

/* @section Operator */
public:
    constexpr const Rect operator+(const Rect&) const noexcept;
    constexpr const Rect operator-(const Rect&) const noexcept;
    constexpr const Rect operator*(_ValueType) const noexcept;
    constexpr const Rect operator/(DevideType) const;
    constexpr const Rect operator+() const noexcept;
    constexpr const Rect operator-() const noexcept;
    Rect& operator+=(const Rect&) noexcept;
    Rect& operator-=(const Rect&) noexcept;
    Rect& operator*=(_ValueType) noexcept;
    Rect& operator/=(DevideType);
    constexpr bool operator==(const Rect&) const noexcept;
    constexpr bool operator!=(const Rect&) const noexcept;

/* @section Public method */
public:
    /**
     * @brief                       Converts value to a string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @return                      The length of string converted.
     */
    template <std::size_t _BufferSize>
    int32_t ToString(char(&destBuffer)[_BufferSize]) const;

    /**
     * @brief                       Converts value to a string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @param [in] bufferSize       The size of destBuffer.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destBuffer, std::size_t bufferSize) const;
    
    /* @return  Converts value to a string. */
    std::string ToString() const;

/* @section Public variable */
public:
    _ValueType bottom;
    _ValueType top;
    _ValueType width;
    _ValueType height;

	static const Rect One;		// 0, 0, 0, 0
	static const Rect Zero;	    // 1, 1, 1, 1
	static const Rect MinusOne;	// -1, -1, -1, -1
};

template <typename _ValueType>
constexpr Rect<_ValueType> MakeRect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept
{
    return {bottom, top, width, height};
}

using IntRect = Rect<int32_t>;
using FloatRect = Rect<float>;
using DoubleRect = Rect<double>;

template <typename _ValueType>
constexpr Rect<_ValueType>::Rect() noexcept :
    bottom{},
    top{},
    width{},
    height{}
{
}

template <typename _ValueType>
constexpr Rect<_ValueType>::Rect(_ValueType bottom, _ValueType top, _ValueType width, _ValueType height) noexcept :
    bottom( bottom),
    top(top),
    width(width),
    height(height)
{
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator+(const Rect& rhs) const noexcept
{
    return Rect(bottom + rhs.bottom, top + rhs.top, width + rhs.width, height + rhs.height);
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator-(const Rect& rhs) const noexcept
{
    return Rect(bottom - rhs.bottom, top - rhs.top, width - rhs.width, height - rhs.height);
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return Rect(bottom * rhs, top * rhs, width * rhs, height * rhs);
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator/(DevideType rhs) const
{
    DevideType inverse = 1.0f / rhs;

    return Rect((_ValueType)((DevideType)bottom * inverse),
                 (_ValueType)((DevideType)top * inverse),
                 (_ValueType)((DevideType)width * inverse),
                 (_ValueType)((DevideType)height * inverse));
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator+() const noexcept
{
	return *this;
}

template <typename _ValueType>
constexpr const Rect<_ValueType> Rect<_ValueType>::operator-() const noexcept
{
	return Rect(-bottom, -top, -width, -height);
}

template <typename _ValueType>
inline Rect<_ValueType>& Rect<_ValueType>::operator+=(const Rect& rhs) noexcept
{
	bottom += rhs.bottom;
    top += rhs.top;
	width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename _ValueType>
inline Rect<_ValueType>& Rect<_ValueType>::operator-=(const Rect& rhs) noexcept
{
    bottom -= rhs.bottom;
    top -= rhs.top;
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename _ValueType>
inline Rect<_ValueType>& Rect<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    bottom *= rhs;
    top *= rhs;
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename _ValueType>
inline Rect<_ValueType>& Rect<_ValueType>::operator/=(DevideType rhs)
{
	DevideType inverse = 1.0f / rhs;

    bottom = (_ValueType)((DevideType)bottom * inverse);
    top = (_ValueType)((DevideType)top * inverse);
    width = (_ValueType)((DevideType)width * inverse);
    height = (_ValueType)((DevideType)height * inverse);

	return *this;
}

template <typename _ValueType>
constexpr bool Rect<_ValueType>::operator==(const Rect& rhs) const noexcept
{
	return (bottom == rhs.bottom && top == rhs.top && width == rhs.width && height == rhs.height);
}

template <typename _ValueType>
constexpr bool Rect<_ValueType>::operator!=(const Rect& rhs) const noexcept
{
    return (bottom != rhs.bottom && top != rhs.top && width != rhs.width && height != rhs.height);
}

template<typename _ValueType>
template<std::size_t _BufferSize>
inline int32_t Rect<_ValueType>::ToString(char(&destBuffer)[_BufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * _BufferSize, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename _ValueType>
inline int32_t Rect<_ValueType>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename _ValueTy>
inline std::string Rect<_ValueTy>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
