/**
 * @filename    TRect.h
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
struct TRect;

template <typename Ty>
struct TRect<Ty>
{
private:
    using DevideTy = std::conditional_t<std::is_floating_point<Ty>::value, Ty, float>;

/**
 * @section Ctor/Dtor
 */
public:
    /* @brief   Constructor that initializes members to 0 */
    constexpr TRect() noexcept;

    /* @brief   Constructor that initializes the member with the specified value */
    constexpr TRect(Ty bottom, Ty top, Ty width, Ty height) noexcept;

/**
 * @section Operator
 */
public:
    constexpr const TRect operator+(const TRect&) const noexcept;
    constexpr const TRect operator-(const TRect&) const noexcept;
    constexpr const TRect operator*(Ty) const noexcept;
    constexpr const TRect operator/(DevideTy) const;
    constexpr const TRect operator+() const noexcept;
    constexpr const TRect operator-() const noexcept;
    TRect& operator+=(const TRect&) noexcept;
    TRect& operator-=(const TRect&) noexcept;
    TRect& operator*=(Ty) noexcept;
    TRect& operator/=(DevideTy);
    constexpr bool operator==(const TRect&) const noexcept;
    constexpr bool operator!=(const TRect&) const noexcept;

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
    Ty bottom;
    Ty top;
    Ty width;
    Ty height;

	static const TRect One;		    // 0, 0, 0, 0
	static const TRect Zero;	    // 1, 1, 1, 1
	static const TRect MinusOne;	// -1, -1, -1, -1
};

template <typename Ty>
constexpr TRect<Ty> MakeRect(Ty bottom, Ty top, Ty width, Ty height) noexcept
{
    return {bottom, top, width, height};
}

using TIntRect = TRect<int32_t>;
using TFloatRect = TRect<float>;
using TDoubleRect = TRect<double>;

template <typename Ty>
constexpr TRect<Ty>::TRect() noexcept :
    bottom{},
    top{},
    width{},
    height{}
{
}

template <typename Ty>
constexpr TRect<Ty>::TRect(Ty _bottom, Ty _top, Ty _width, Ty _height) noexcept :
    bottom(_bottom),
    top(_top),
    width(_width),
    height(_height)
{
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator+(const TRect& rhs) const noexcept
{
    return TRect(bottom + rhs.bottom, top + rhs.top, width + rhs.width, height + rhs.height);
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator-(const TRect& rhs) const noexcept
{
    return TRect(bottom - rhs.bottom, top - rhs.top, width - rhs.width, height - rhs.height);
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator*(Ty rhs) const noexcept
{
    return TRect(bottom * rhs, top * rhs, width * rhs, height * rhs);
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator/(DevideTy rhs) const
{
    DevideTy inverse = 1.0f / rhs;

    return TRect((Ty)((DevideTy)bottom * inverse), 
                 (Ty)((DevideTy)top * inverse),
                 (Ty)((DevideTy)width * inverse),
                 (Ty)((DevideTy)height * inverse));
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
constexpr const TRect<Ty> TRect<Ty>::operator-() const noexcept
{
	return TRect(-bottom, -top, -width, -height);
}

template <typename Ty>
inline TRect<Ty>& TRect<Ty>::operator+=(const TRect& rhs) noexcept
{
	bottom += rhs.bottom;
    top += rhs.top;
	width += rhs.width;
    height += rhs.height;

	return *this;
}

template <typename Ty>
inline TRect<Ty>& TRect<Ty>::operator-=(const TRect& rhs) noexcept
{
    bottom -= rhs.bottom;
    top -= rhs.top;
    width -= rhs.width;
    height -= rhs.height;

	return *this;
}

template <typename Ty>
inline TRect<Ty>& TRect<Ty>::operator*=(Ty rhs) noexcept
{
    bottom *= rhs;
    top *= rhs;
    width *= rhs;
    height *= rhs;

	return *this;
}

template <typename Ty>
inline TRect<Ty>& TRect<Ty>::operator/=(DevideTy rhs)
{
	DevideTy inverse = 1.0f / rhs;

    bottom = (Ty)((DevideTy)bottom * inverse);
    top = (Ty)((DevideTy)top * inverse);
    width = (Ty)((DevideTy)width * inverse);
    height = (Ty)((DevideTy)height * inverse);

	return *this;
}

template <typename Ty>
constexpr bool TRect<Ty>::operator==(const TRect& rhs) const noexcept
{
	return (bottom == rhs.bottom && top == rhs.top && width == rhs.width && height == rhs.height);
}

template <typename Ty>
constexpr bool TRect<Ty>::operator!=(const TRect& rhs) const noexcept
{
    return (bottom != rhs.bottom || top != rhs.top || width != rhs.width || height != rhs.height);
}

template<typename Ty>
template<std::size_t N>
inline int32_t TRect<Ty>::ToString(char(&destBuffer)[N]) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename Ty>
inline int32_t TRect<Ty>::ToString(char* destBuffer, std::size_t bufferSize) const
{
#if _MSC_VER
    return sprintf_s(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#else
    return snprintf(destBuffer, sizeof(destBuffer[0]) * bufferSize, "%d %d %d %d", bottom, top, width, height);
#endif
}

template<typename Ty>
inline std::string TRect<Ty>::ToString() const
{
    char buffer[128]{};
    this->ToString(buffer);

    return buffer;
}

} /* namespace math */
} /* namespace tgon */