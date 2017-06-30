/**
 * @filename    Point.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <string>

#include "Core/Utility/TypeTraits.h"

namespace tgon
{
namespace math
{

template <typename Ty,
          typename = utility::EnableIfArithmetic<Ty>>
struct Point;

template <typename Ty>
struct Point<Ty>
{
private:
    using DevideTy = typename std::conditional<std::is_floating_point<Ty>::value, Ty, float>::type;

/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Point() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Point(Ty x, Ty y) noexcept;

/* @section Operator */
public:
    constexpr const Point operator+(const Point&) const noexcept;
    constexpr const Point operator-(const Point&) const noexcept;
    constexpr const Point operator*(Ty) const noexcept;
    constexpr const Point operator/(DevideTy) const;
    constexpr const Point operator+() const noexcept;
    constexpr const Point operator-() const noexcept;
    Point& operator+=(const Point&) noexcept;
    Point& operator-=(const Point&) noexcept;
    Point& operator*=(Ty) noexcept;
    Point& operator/=(DevideTy);
    constexpr bool operator==(const Point&) const noexcept;
    constexpr bool operator!=(const Point&) const noexcept;

    template <typename CastToTy>
    constexpr operator Point<CastToTy>() const noexcept;

/* @section Public method */
public:
    /**
     * @brief                       Converts to string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @return                      The length of string converted.
     */
    template <std::size_t N>
    int32_t ToString(char(&destBuffer)[N]) const;

    /**
     * @brief                       Converts to string.
     * @param [out] destBuffer      The destination of the string to be written.
     * @param [in] bufferSize       The size of destBuffer.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destBuffer, std::size_t bufferSize) const;
    
    /* @return  A string converted. */
    std::string ToString() const;

/* @section Public variable */
public:
    Ty x;
    Ty y;

	static const Point One;		// 1, 1
	static const Point Zero;	    // 0, 0
	static const Point MinusOne;	// -1, -1
};

template <typename Ty>
constexpr Point<Ty> MakePoint(Ty x, Ty y) noexcept
{
    return {x, y};
}

using IntPoint = Point<int32_t>;
using FloatPoint = Point<float>;
using DoublePoint = Point<double>;

template <typename Ty>
constexpr Point<Ty>::Point() noexcept :
    x{},
    y{}
{
}

template <typename Ty>
constexpr Point<Ty>::Point(Ty x, Ty y) noexcept :
    x(x),
    y(y)
{
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator+(const Point& rhs) const noexcept
{
    return Point(x + rhs.x, y + rhs.y);
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator-(const Point& rhs) const noexcept
{
    return Point(x - rhs.x, y - rhs.y);
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator*(Ty rhs) const noexcept
{
    return Point(x * rhs, y * rhs);
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator/(DevideTy rhs) const
{
    return Point((Ty)((DevideTy)x / (DevideTy)rhs),
                  (Ty)((DevideTy)y / (DevideTy)rhs));
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const Point<Ty> Point<Ty>::operator-() const noexcept
{
	return Point(-x, -y);
}

template <typename Ty>
inline Point<Ty>& Point<Ty>::operator+=(const Point& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;

	return *this;
}

template <typename Ty>
inline Point<Ty>& Point<Ty>::operator-=(const Point& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;

	return *this;
}

template <typename Ty>
inline Point<Ty>& Point<Ty>::operator*=(Ty rhs) noexcept
{
    x *= rhs;
    y *= rhs;

	return *this;
}

template <typename Ty>
inline Point<Ty>& Point<Ty>::operator/=(DevideTy rhs)
{
    x = (Ty)((DevideTy)x / rhs);
    y = (Ty)((DevideTy)y / rhs);

	return *this;
}

template <typename Ty>
inline constexpr bool Point<Ty>::operator==(const Point& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y);
}

template <typename Ty>
inline constexpr bool Point<Ty>::operator!=(const Point& rhs) const noexcept
{
    return (x != rhs.x || y != rhs.y);
}

template<typename Ty>
template<typename CastToTy>
constexpr Point<Ty>::operator Point<CastToTy>() const noexcept
{
    return Point<CastToTy>((CastToTy)x, (CastToTy)y);
}

template<typename Ty>
template<std::size_t N>
inline int32_t Point<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * N, "%d %d", x, y);
#endif
}

template<typename Ty>
inline int32_t Point<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#endif
}

template<typename Ty>
inline std::string Point<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
