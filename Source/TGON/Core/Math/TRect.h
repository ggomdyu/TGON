/**
 * @filename    TRect.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <type_traits>
#include <cassert>

namespace tgon {
namespace math {

template <typename Ty>
struct TRect
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
    const TRect operator+(const TRect&) const noexcept;
    const TRect operator-(const TRect&) const noexcept;
    const TRect operator*(Ty) const noexcept;
    const TRect operator/(DevideTy) const;
    const TRect operator+() const noexcept;
    const TRect operator-() const noexcept;
    TRect& operator+=(const TRect&) noexcept;
    TRect& operator-=(const TRect&) noexcept;
    TRect& operator*=(Ty) noexcept;
    TRect& operator/=(DevideTy);
    bool operator==(const TRect&) const noexcept;
    bool operator!=(const TRect&) const noexcept;

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

using TIntRect = TRect<int>;
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
inline const TRect<Ty> TRect<Ty>::operator+(const TRect& rhs) const noexcept
{
    return TRect(bottom + rhs.bottom, top + rhs.top, width + rhs.width, height + rhs.height);
}

template <typename Ty>
inline const TRect<Ty> TRect<Ty>::operator-(const TRect& rhs) const noexcept
{
    return TRect(bottom - rhs.bottom, top - rhs.top, width - rhs.width, height - rhs.height);
}

template <typename Ty>
inline const TRect<Ty> TRect<Ty>::operator*(Ty rhs) const noexcept
{
    return TRect(bottom * rhs, top * rhs, width * rhs, height * rhs);
}

template <typename Ty>
inline const TRect<Ty> TRect<Ty>::operator/(DevideTy rhs) const
{
    assert(rhs != Ty(0) && "TRect elements can't be divided by zero.");

    DevideTy inverse = 1.0f / rhs;

    return TRect((Ty)((DevideTy)bottom * inverse), 
                 (Ty)((DevideTy)top * inverse),
                 (Ty)((DevideTy)width * inverse),
                 (Ty)((DevideTy)height * inverse));
}

template <typename Ty>
inline const TRect<Ty> TRect<Ty>::operator+() const noexcept
{
	return *this;
}

template <typename Ty>
inline const TRect<Ty> TRect<Ty>::operator-() const noexcept
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
    assert(rhs != (Ty)0 && "TRect elements can't be divided by zero.");

	DevideTy inverse = 1.0f / rhs;

    bottom = (Ty)((DevideTy)bottom * inverse);
    top = (Ty)((DevideTy)top * inverse);
    width = (Ty)((DevideTy)width * inverse);
    height = (Ty)((DevideTy)height * inverse);

	return *this;
}

template <typename Ty>
inline bool TRect<Ty>::operator==(const TRect& rhs) const noexcept
{
	return (bottom == rhs.bottom && top == rhs.top && width == rhs.width && height == rhs.height);
}

template <typename Ty>
inline bool TRect<Ty>::operator!=(const TRect& rhs) const noexcept
{
    return (bottom != rhs.bottom || top != rhs.top || width != rhs.width || height != rhs.height);
}

} /* namespace math */
} /* namespace tgon */