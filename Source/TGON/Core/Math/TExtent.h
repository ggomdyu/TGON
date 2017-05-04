/**
 * @filename    TExtent.h
 * @author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include "../Platform/TConfig.h"

#include <type_traits>
#include <cassert>
#include <cstdint>

namespace tgon {
namespace math {

template <typename Ty>
struct TExtent
{
private:
    using DevideTy = std::conditional_t<std::is_floating_point<Ty>::value, Ty, float>;

/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr TExtent() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr TExtent(Ty x, Ty y) noexcept;

/**
 * @section Operator
 */
public:
    const TExtent operator+(const TExtent&) const noexcept;
    const TExtent operator-(const TExtent&) const noexcept;
    const TExtent operator*(Ty) const noexcept;
    const TExtent operator/(DevideTy) const;
    const TExtent operator+() const noexcept;
    const TExtent operator-() const noexcept;
    TExtent& operator+=(const TExtent&) noexcept;
    TExtent& operator-=(const TExtent&) noexcept;
    TExtent& operator*=(Ty) noexcept;
    TExtent& operator/=(DevideTy);
    constexpr bool operator==(const TExtent&) const noexcept;
    constexpr bool operator!=(const TExtent&) const noexcept;

/**
 * @section Public variables
 */
public:
    Ty width;
    Ty height;

	static const TExtent One;		// 1, 1
	static const TExtent Zero;	    // 0, 0
	static const TExtent MinusOne;	// -1, -1
};

using TIntExtent = TExtent<int>;
using TFloatExtent = TExtent<float>;
using TDoubleExtent = TExtent<double>;

template <typename Ty>
constexpr TExtent<Ty>::TExtent() noexcept :
    width{},
    height{}
{
}

template <typename Ty>
constexpr TExtent<Ty>::TExtent(Ty _x, Ty _y) noexcept :
    width(_x),
    height(_y)
{
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator+(const TExtent& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator-(const TExtent& rhs) const noexcept
{
    return TExtent(X - rhs.width, height - rhs.height);
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator*(Ty rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator/(DevideTy rhs) const
{
    assert(rhs != Ty(0) && "TExtent elements can't be divided by zero.");

    return TExtent((Ty)((DevideTy)width / (DevideTy)rhs),
                  (Ty)((DevideTy)height / (DevideTy)rhs));
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
inline const TExtent<Ty> TExtent<Ty>::operator-() const noexcept
{
	return TExtent(-width, -height);
}

template <typename Ty>
inline TExtent<Ty>& TExtent<Ty>::operator+=(const TExtent& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename Ty>
inline TExtent<Ty>& TExtent<Ty>::operator-=(const TExtent& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename Ty>
inline TExtent<Ty>& TExtent<Ty>::operator*=(Ty rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename Ty>
inline TExtent<Ty>& TExtent<Ty>::operator/=(DevideTy rhs)
{
    assert(rhs != (Ty)0 && "TExtent elements can't be divided by zero.");

    width = (Ty)((DevideTy)width / rhs);
    height = (Ty)((DevideTy)height / rhs);

	return *this;
}

template <typename Ty>
inline constexpr bool TExtent<Ty>::operator==(const TExtent& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename Ty>
inline constexpr bool TExtent<Ty>::operator!=(const TExtent& rhs) const noexcept
{
    return (width != rhs.width || height != rhs.height);
}

} /* namespace math */
} /* namespace tgon */