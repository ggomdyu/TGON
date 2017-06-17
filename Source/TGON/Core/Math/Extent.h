/**
 * @filename    Extent.h
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
struct Extent2D;

template <typename Ty>
struct Extent2D<Ty>
{
private:
    using DevideTy = typename std::conditional<std::is_floating_point<Ty>::value, Ty, float>::type;

/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Extent2D() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Extent2D(Ty width, Ty height) noexcept;

/**
 * @section Operator
 */
public:
    constexpr const Extent2D operator+(const Extent2D&) const noexcept;
    constexpr const Extent2D operator-(const Extent2D&) const noexcept;
    constexpr const Extent2D operator*(Ty) const noexcept;
    constexpr const Extent2D operator/(DevideTy) const;
    constexpr const Extent2D operator+() const noexcept;
    constexpr const Extent2D operator-() const noexcept;
    Extent2D& operator+=(const Extent2D&) noexcept;
    Extent2D& operator-=(const Extent2D&) noexcept;
    Extent2D& operator*=(Ty) noexcept;
    Extent2D& operator/=(DevideTy);
    constexpr bool operator==(const Extent2D&) const noexcept;
    constexpr bool operator!=(const Extent2D&) const noexcept;

    template <typename CastToTy>
    constexpr operator Extent2D<CastToTy>() const noexcept;

/**
 * @section Public method
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
 * @section Public variable
 */
public:
    Ty width;
    Ty height;

	static const Extent2D One;		// 1, 1
	static const Extent2D Zero;	    // 0, 0
	static const Extent2D MinusOne;	// -1, -1
};

template <typename Ty>
constexpr Extent2D<Ty> MakeExtent(Ty width, Ty height) noexcept
{
    return {width, height};
}

using IntExtent2D = Extent2D<int32_t>;
using FloatExtent2D = Extent2D<float>;

template<typename Ty>
constexpr Extent2D<Ty>::Extent2D() noexcept :
    width{},
    height{}
{
}

template <typename Ty>
constexpr Extent2D<Ty>::Extent2D(Ty width, Ty height) noexcept :
    width(width),
    height(height)
{
}

template<typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator+(const Extent2D& rhs) const noexcept
{
    return TExtent(width + rhs.width, height + rhs.height);
}

template <typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator-(const Extent2D& rhs) const noexcept
{
    return TExtent(width - rhs.width, height - rhs.height);
}

template <typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator*(Ty rhs) const noexcept
{
    return TExtent(width * rhs, height * rhs);
}

template <typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator/(DevideTy rhs) const
{
    return TExtent((Ty)((DevideTy)width / (DevideTy)rhs),
                  (Ty)((DevideTy)height / (DevideTy)rhs));
}

template <typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const Extent2D<Ty> Extent2D<Ty>::operator-() const noexcept
{
	return TExtent(-width, -height);
}

template <typename Ty>
inline Extent2D<Ty>& Extent2D<Ty>::operator+=(const Extent2D& rhs) noexcept
{
    width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename Ty>
inline Extent2D<Ty>& Extent2D<Ty>::operator-=(const Extent2D& rhs) noexcept
{
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename Ty>
inline Extent2D<Ty>& Extent2D<Ty>::operator*=(Ty rhs) noexcept
{
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename Ty>
inline Extent2D<Ty>& Extent2D<Ty>::operator/=(DevideTy rhs)
{
    width = (Ty)((DevideTy)width / rhs);
    height = (Ty)((DevideTy)height / rhs);

	return *this;
}

template <typename Ty>
inline constexpr bool Extent2D<Ty>::operator==(const Extent2D& rhs) const noexcept
{
	return (width == rhs.width && height == rhs.height);
}

template <typename Ty>
inline constexpr bool Extent2D<Ty>::operator!=(const Extent2D& rhs) const noexcept
{
    return (width != rhs.width || height != rhs.height);
}

template<typename Ty>
template<typename CastToTy>
constexpr Extent2D<Ty>::operator Extent2D<CastToTy>() const noexcept
{
    return Extent2D<CastToTy>((CastToTy)width, (CastToTy)height);
}

template<typename Ty>
template<std::size_t N>
inline int32_t Extent2D<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * N, "%d %d", width, height);
#endif
}

template<typename Ty>
inline int32_t Extent2D<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d", width, height);
#endif
}

template<typename Ty>
inline std::string Extent2D<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
