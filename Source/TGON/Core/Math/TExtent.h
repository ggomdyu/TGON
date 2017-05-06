/**
 * @filename    TExtent.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include "Core/Platform/TConfig.h"

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
    constexpr TExtent(Ty width, Ty height) noexcept;

/**
 * @section Operator
 */
public:
    constexpr const TExtent operator+(const TExtent&) const noexcept;
    constexpr const TExtent operator-(const TExtent&) const noexcept;
    constexpr const TExtent operator*(Ty) const noexcept;
    constexpr const TExtent operator/(DevideTy) const;
    constexpr const TExtent operator+() const noexcept;
    constexpr const TExtent operator-() const noexcept;
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

template <typename Ty>
constexpr TExtent<Ty> MakeExtent(Ty width, Ty height) noexcept
{
    return {width, height};
}

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
constexpr TExtent<Ty>::TExtent(Ty _width, Ty _height) noexcept :
    width(_width),
    height(_height)
{
}

template<typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator+(const TExtent& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator-(const TExtent& rhs) const noexcept
{
    return TExtent(width - rhs.width, height - rhs.height);
}

template <typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator*(Ty rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator/(DevideTy rhs) const
{
    assert(rhs != Ty(0) && "TExtent elements can't be divided by zero.");

    return TExtent((Ty)((DevideTy)width / (DevideTy)rhs),
                  (Ty)((DevideTy)height / (DevideTy)rhs));
}

template <typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const TExtent<Ty> TExtent<Ty>::operator-() const noexcept
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