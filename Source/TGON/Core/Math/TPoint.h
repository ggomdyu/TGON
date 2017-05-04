/**
 * @filename    TPoint.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include "../Platform/TConfig.h"

#include <type_traits>
#include <cassert>
#include <cstdint>

namespace tgon {
namespace math {

template <typename Ty>
struct TPoint
{
private:
    using DevideTy = std::conditional_t<std::is_floating_point<Ty>::value, Ty, float>;

/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr TPoint() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr TPoint(Ty x, Ty y) noexcept;

/**
 * @section Operator
 */
public:
    const TPoint operator+(const TPoint&) const noexcept;
    const TPoint operator-(const TPoint&) const noexcept;
    const TPoint operator*(Ty) const noexcept;
    const TPoint operator/(DevideTy) const;
    const TPoint operator+() const noexcept;
    const TPoint operator-() const noexcept;
    TPoint& operator+=(const TPoint&) noexcept;
    TPoint& operator-=(const TPoint&) noexcept;
    TPoint& operator*=(Ty) noexcept;
    TPoint& operator/=(DevideTy);
    constexpr bool operator==(const TPoint&) const noexcept;
    constexpr bool operator!=(const TPoint&) const noexcept;

/**
 * @section Public variables
 */
public:
    Ty x;
    Ty y;

	static const TPoint One;		// 1, 1
	static const TPoint Zero;	    // 0, 0
	static const TPoint MinusOne;	// -1, -1
};

using TIntPoint = TPoint<int>;
using TFloatPoint = TPoint<float>;
using TDoublePoint = TPoint<double>;

template <typename Ty>
constexpr TPoint<Ty>::TPoint() noexcept :
    x{},
    y{}
{
}

template <typename Ty>
constexpr TPoint<Ty>::TPoint(Ty _x, Ty _y) noexcept :
    x(_x),
    y(_y)
{
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator+(const TPoint& rhs) const noexcept
{
    return TPoint(x + rhs.x, y + rhs.y);
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator-(const TPoint& rhs) const noexcept
{
    return TPoint(X - rhs.x, y - rhs.y);
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator*(Ty rhs) const noexcept
{
    return TPoint(x * rhs, y * rhs);
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator/(DevideTy rhs) const
{
    assert(rhs != Ty(0) && "TPoint elements can't be divided by zero.");

    return TPoint((Ty)((DevideTy)x / (DevideTy)rhs),
                  (Ty)((DevideTy)y / (DevideTy)rhs));
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
inline const TPoint<Ty> TPoint<Ty>::operator-() const noexcept
{
	return TPoint(-x, -y);
}

template <typename Ty>
inline TPoint<Ty>& TPoint<Ty>::operator+=(const TPoint& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;

	return *this;
}

template <typename Ty>
inline TPoint<Ty>& TPoint<Ty>::operator-=(const TPoint& rhs) noexcept
{
    x -= rhs.x;
    y -= rhs.y;

	return *this;
}

template <typename Ty>
inline TPoint<Ty>& TPoint<Ty>::operator*=(Ty rhs) noexcept
{
    x *= rhs;
    y *= rhs;

	return *this;
}

template <typename Ty>
inline TPoint<Ty>& TPoint<Ty>::operator/=(DevideTy rhs)
{
    assert(rhs != (Ty)0 && "TPoint elements can't be divided by zero.");

    x = (Ty)((DevideTy)x / rhs);
    y = (Ty)((DevideTy)y / rhs);

	return *this;
}

template <typename Ty>
inline constexpr bool TPoint<Ty>::operator==(const TPoint& rhs) const noexcept
{
	return (x == rhs.x && y == rhs.y);
}

template <typename Ty>
inline constexpr bool TPoint<Ty>::operator!=(const TPoint& rhs) const noexcept
{
    return (x != rhs.x || y != rhs.y);
}

} /* namespace math */
} /* namespace tgon */
