/**
 * @filename    Point.h
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
struct Point
{
/* @section Public type */
public:
    using DevideType = typename std::conditional<std::is_floating_point<_ValueType>::value, _ValueType, float>::type;
    using ValueType = _ValueType;

/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Point() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Point(_ValueType x, _ValueType y) noexcept;

/* @section Operator */
public:
    constexpr const Point operator+(const Point&) const noexcept;
    constexpr const Point operator-(const Point&) const noexcept;
    constexpr const Point operator*(_ValueType) const noexcept;
    constexpr const Point operator/(DevideType) const;
    constexpr const Point operator+() const noexcept;
    constexpr const Point operator-() const noexcept;
    Point& operator+=(const Point&) noexcept;
    Point& operator-=(const Point&) noexcept;
    Point& operator*=(_ValueType) noexcept;
    Point& operator/=(DevideType);
    constexpr bool operator==(const Point&) const noexcept;
    constexpr bool operator!=(const Point&) const noexcept;

    template <typename _CastToType>
    constexpr operator Point<_CastToType>() const noexcept;

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
    _ValueType x;
    _ValueType y;

	static const Point One;         // 1, 1
    static const Point Zero;        // 0, 0
	static const Point MinusOne;    // -1, -1
};

template <typename _ValueType>
constexpr Point<_ValueType> MakePoint(_ValueType x, _ValueType y) noexcept
{
    return {x, y};
}

using IntPoint = Point<int32_t>;
using FloatPoint = Point<float>;
using DoublePoint = Point<double>;

template <typename _ValueType>
constexpr Point<_ValueType>::Point() noexcept :
    x{},
    y{}
{
}

template <typename _ValueType>
constexpr Point<_ValueType>::Point(_ValueType x, _ValueType y) noexcept :
    x(x),
    y(y)
{
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator+(const Point& rhs) const noexcept
{
    return Point(x + rhs.x, y + rhs.y);
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator-(const Point& rhs) const noexcept
{
    return Point(x - rhs.x, y - rhs.y);
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator*(_ValueType rhs) const noexcept
{
    return Point(x * rhs, y * rhs);
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator/(DevideType rhs) const
{
    return Point((_ValueType)((DevideType)x / (DevideType)rhs),
                 (_ValueType)((DevideType)y / (DevideType)rhs));
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator+() const noexcept
{
	return *this;
}

template <typename _ValueType>
constexpr const Point<_ValueType> Point<_ValueType>::operator-() const noexcept
{
	return Point(-x, -y);
}

template <typename _ValueType>
inline Point<_ValueType>& Point<_ValueType>::operator+=(const Point& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;

	return *this;
}

template <typename _ValueType>
inline Point<_ValueType>& Point<_ValueType>::operator-=(const Point& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;

	return *this;
}

template <typename _ValueType>
inline Point<_ValueType>& Point<_ValueType>::operator*=(_ValueType rhs) noexcept
{
    x *= rhs;
    y *= rhs;

	return *this;
}

template <typename _ValueType>
inline Point<_ValueType>& Point<_ValueType>::operator/=(DevideType rhs)
{
    x = (_ValueType)((DevideType)x / rhs);
    y = (_ValueType)((DevideType)y / rhs);

	return *this;
}

template <typename _ValueType>
inline constexpr bool Point<_ValueType>::operator==(const Point& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y);
}

template <typename _ValueType>
inline constexpr bool Point<_ValueType>::operator!=(const Point& rhs) const noexcept
{
    return (x != rhs.x && y != rhs.y);
}

template<typename _ValueType>
template<typename _CastToType>
constexpr Point<_ValueType>::operator Point<_CastToType>() const noexcept
{
    return Point<_CastToType>((_CastToType)x, (_CastToType)y);
}

template<typename _ValueType>
template<std::size_t _BufferSize>
inline int32_t Point<_ValueType>::ToString(char(&destBuffer)[_BufferSize]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * _BufferSize, "%d %d", x, y);
#endif
}

template<typename _ValueType>
inline int32_t Point<_ValueType>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#endif
}

template<typename _ValueType>
inline std::string Point<_ValueType>::ToString() const
{
    char buffer[128] {};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
