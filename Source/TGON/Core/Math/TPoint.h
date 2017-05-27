/**
 * @filename    TPoint.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <type_traits>
#include <cstdint>
#include <string>

#include "Core/Utility/TTypeTraits.h"

namespace tgon {
namespace math {

template <typename Ty,
          typename = utility::EnableIfArithmetic<Ty>>
struct TPoint;

template <typename Ty>
struct TPoint<Ty>
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
    constexpr const TPoint operator+(const TPoint&) const noexcept;
    constexpr const TPoint operator-(const TPoint&) const noexcept;
    constexpr const TPoint operator*(Ty) const noexcept;
    constexpr const TPoint operator/(DevideTy) const;
    constexpr const TPoint operator+() const noexcept;
    constexpr const TPoint operator-() const noexcept;
    TPoint& operator+=(const TPoint&) noexcept;
    TPoint& operator-=(const TPoint&) noexcept;
    TPoint& operator*=(Ty) noexcept;
    TPoint& operator/=(DevideTy);
    constexpr bool operator==(const TPoint&) const noexcept;
    constexpr bool operator!=(const TPoint&) const noexcept;

    template <typename CastToTy>
    constexpr operator TPoint<CastToTy>() const noexcept;

/**
 * @section Public command method
 */
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
    
    /* @return  The string converted. */
    std::string ToString() const;

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

template <typename Ty>
constexpr TPoint<Ty> MakePoint(Ty x, Ty y) noexcept
{
    return {x, y};
}

using TIntPoint = TPoint<int32_t>;
using TFloatPoint = TPoint<float>;
using TDoublePoint = TPoint<double>;

template <typename Ty>
constexpr TPoint<Ty>::TPoint() noexcept :
    x{},
    y{}
{
}

template <typename Ty>
constexpr TPoint<Ty>::TPoint(Ty x, Ty y) noexcept :
    x(x),
    y(y)
{
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator+(const TPoint& rhs) const noexcept
{
    return TPoint(x + rhs.x, y + rhs.y);
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator-(const TPoint& rhs) const noexcept
{
    return TPoint(x - rhs.x, y - rhs.y);
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator*(Ty rhs) const noexcept
{
    return TPoint(x * rhs, y * rhs);
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator/(DevideTy rhs) const
{
    return TPoint((Ty)((DevideTy)x / (DevideTy)rhs),
                  (Ty)((DevideTy)y / (DevideTy)rhs));
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const TPoint<Ty> TPoint<Ty>::operator-() const noexcept
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

template<typename Ty>
template<typename CastToTy>
constexpr TPoint<Ty>::operator TPoint<CastToTy>() const noexcept
{
    return TPoint<CastToTy>((CastToTy)x, (CastToTy)y);
}

template<typename Ty>
template<std::size_t N>
inline int32_t TPoint<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#endif
}

template<typename Ty>
inline int32_t TPoint<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", x, y);
#endif
}

template<typename Ty>
inline std::string TPoint<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
