/**
 * @filename    Rect.h
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
struct Rect;

template <typename Ty>
struct Rect<Ty>
{
private:
    using DevideTy = typename std::conditional<std::is_floating_point<Ty>::value, Ty, float>::type;

/* @section Ctor/Dtor */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr Rect() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr Rect(Ty bottom, Ty top, Ty width, Ty height) noexcept;

/* @section Operator */
public:
    constexpr const Rect operator+(const Rect&) const noexcept;
    constexpr const Rect operator-(const Rect&) const noexcept;
    constexpr const Rect operator*(Ty) const noexcept;
    constexpr const Rect operator/(DevideTy) const;
    constexpr const Rect operator+() const noexcept;
    constexpr const Rect operator-() const noexcept;
    Rect& operator+=(const Rect&) noexcept;
    Rect& operator-=(const Rect&) noexcept;
    Rect& operator*=(Ty) noexcept;
    Rect& operator/=(DevideTy);
    constexpr bool operator==(const Rect&) const noexcept;
    constexpr bool operator!=(const Rect&) const noexcept;

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
    Ty bottom;
    Ty top;
    Ty width;
    Ty height;

	static const Rect One;		    // 0, 0, 0, 0
	static const Rect Zero;	    // 1, 1, 1, 1
	static const Rect MinusOne;	// -1, -1, -1, -1
};

template <typename Ty>
constexpr Rect<Ty> MakeRect(Ty bottom, Ty top, Ty width, Ty height) noexcept
{
    return {bottom, top, width, height};
}

using IntRect = Rect<int32_t>;
using FloatRect = Rect<float>;
using DoubleRect = Rect<double>;

template <typename Ty>
constexpr Rect<Ty>::Rect() noexcept :
    bottom{},
    top{},
    width{},
    height{}
{
}

template <typename Ty>
constexpr Rect<Ty>::Rect(Ty bottom, Ty top, Ty width, Ty height) noexcept :
    bottom( bottom),
    top(top),
    width(width),
    height(height)
{
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator+(const Rect& rhs) const noexcept
{
    return Rect(bottom + rhs.bottom, top + rhs.top, width + rhs.width, height + rhs.height);
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator-(const Rect& rhs) const noexcept
{
    return Rect(bottom - rhs.bottom, top - rhs.top, width - rhs.width, height - rhs.height);
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator*(Ty rhs) const noexcept
{
    return Rect(bottom * rhs, top * rhs, width * rhs, height * rhs);
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator/(DevideTy rhs) const
{
    DevideTy inverse = 1.0f / rhs;

    return Rect((Ty)((DevideTy)bottom * inverse), 
                 (Ty)((DevideTy)top * inverse),
                 (Ty)((DevideTy)width * inverse),
                 (Ty)((DevideTy)height * inverse));
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const Rect<Ty> Rect<Ty>::operator-() const noexcept
{
	return Rect(-bottom, -top, -width, -height);
}

template <typename Ty>
inline Rect<Ty>& Rect<Ty>::operator+=(const Rect& rhs) noexcept
{
	bottom += rhs.bottom;
    top += rhs.top;
	width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename Ty>
inline Rect<Ty>& Rect<Ty>::operator-=(const Rect& rhs) noexcept
{
    bottom -= rhs.bottom;
    top -= rhs.top;
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename Ty>
inline Rect<Ty>& Rect<Ty>::operator*=(Ty rhs) noexcept
{
    bottom *= rhs;
    top *= rhs;
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename Ty>
inline Rect<Ty>& Rect<Ty>::operator/=(DevideTy rhs)
{
	DevideTy inverse = 1.0f / rhs;

    bottom = (Ty)((DevideTy)bottom * inverse);
    top = (Ty)((DevideTy)top * inverse);
    width = (Ty)((DevideTy)width * inverse);
    height = (Ty)((DevideTy)height * inverse);

	return *this;
}

template <typename Ty>
constexpr bool Rect<Ty>::operator==(const Rect& rhs) const noexcept
{
	return (bottom == rhs.bottom && top == rhs.top && width == rhs.width && height == rhs.height);
}

template <typename Ty>
constexpr bool Rect<Ty>::operator!=(const Rect& rhs) const noexcept
{
    return (bottom != rhs.bottom || top != rhs.top || width != rhs.width || height != rhs.height);
}

template<typename Ty>
template<std::size_t N>
inline int32_t Rect<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * N, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename Ty>
inline int32_t Rect<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename Ty>
inline std::string Rect<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */
