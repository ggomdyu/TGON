/**
 * @filename    TExtent.h
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
struct TExtent2D;

template <typename Ty>
struct TExtent2D<Ty>
{
private:
    using DevideTy = std::conditional_t<std::is_floating_point<Ty>::value, Ty, float>;

/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr TExtent2D() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr TExtent2D(Ty width, Ty height) noexcept;

/**
 * @section Operator
 */
public:
    constexpr const TExtent2D operator+(const TExtent2D&) const noexcept;
    constexpr const TExtent2D operator-(const TExtent2D&) const noexcept;
    constexpr const TExtent2D operator*(Ty) const noexcept;
    constexpr const TExtent2D operator/(DevideTy) const;
    constexpr const TExtent2D operator+() const noexcept;
    constexpr const TExtent2D operator-() const noexcept;
    TExtent2D& operator+=(const TExtent2D&) noexcept;
    TExtent2D& operator-=(const TExtent2D&) noexcept;
    TExtent2D& operator*=(Ty) noexcept;
    TExtent2D& operator/=(DevideTy);
    constexpr bool operator==(const TExtent2D&) const noexcept;
    constexpr bool operator!=(const TExtent2D&) const noexcept;

    template <typename CastToTy>
    constexpr operator TExtent2D<CastToTy>() const noexcept;

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
    Ty width;
    Ty height;

	static const TExtent2D One;		// 1, 1
	static const TExtent2D Zero;	    // 0, 0
	static const TExtent2D MinusOne;	// -1, -1
};

template <typename Ty>
constexpr TExtent2D<Ty> MakeExtent(Ty width, Ty height) noexcept
{
    return {width, height};
}

using TIntExtent2D = TExtent2D<int32_t>;
using TFloatExtent2D = TExtent2D<float>;
using TDoubleExtent2D = TExtent2D<double>;

template<typename Ty>
constexpr TExtent2D<Ty>::TExtent2D() noexcept :
    width{},
    height{}
{
}

template <typename Ty>
constexpr TExtent2D<Ty>::TExtent2D(Ty width, Ty height) noexcept :
    width(width),
    height(height)
{
}

template<typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator+(const TExtent2D& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator-(const TExtent2D& rhs) const noexcept
{
    return TExtent(width - rhs.width, height - rhs.height);
}

template <typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator*(Ty rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator/(DevideTy rhs) const
{
    return TExtent((Ty)((DevideTy)width / (DevideTy)rhs),
                  (Ty)((DevideTy)height / (DevideTy)rhs));
}

template <typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const TExtent2D<Ty> TExtent2D<Ty>::operator-() const noexcept
{
	return TExtent(-width, -height);
}

template <typename Ty>
inline TExtent2D<Ty>& TExtent2D<Ty>::operator+=(const TExtent2D& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename Ty>
inline TExtent2D<Ty>& TExtent2D<Ty>::operator-=(const TExtent2D& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename Ty>
inline TExtent2D<Ty>& TExtent2D<Ty>::operator*=(Ty rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename Ty>
inline TExtent2D<Ty>& TExtent2D<Ty>::operator/=(DevideTy rhs)
{
    width = (Ty)((DevideTy)width / rhs);
    height = (Ty)((DevideTy)height / rhs);

	return *this;
}

template <typename Ty>
inline constexpr bool TExtent2D<Ty>::operator==(const TExtent2D& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename Ty>
inline constexpr bool TExtent2D<Ty>::operator!=(const TExtent2D& rhs) const noexcept
{
    return (width != rhs.width || height != rhs.height);
}

template<typename Ty>
template<typename CastToTy>
constexpr TExtent2D<Ty>::operator TExtent2D<CastToTy>() const noexcept
{
    return TExtent2D<CastToTy>((CastToTy)width, (CastToTy)height);
}

template<typename Ty>
template<std::size_t N>
inline int32_t TExtent2D<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#endif
}

template<typename Ty>
inline int32_t TExtent2D<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#endif
}

template<typename Ty>
inline std::string TExtent2D<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */