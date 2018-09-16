/**
 * @file    Color.h
 * @author  ggomdyu
 * @since   05/03/2017
 */

#pragma once
#include <cstdint>
#include <cstdio>

namespace tgon
{

struct Color4b
{
/**@section Public constructor */
public:
    /**@brief   Assigns all components to zero. */
    constexpr Color4b() noexcept;

    /**@brief   Assigns color components with the specified value. */
    constexpr Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;

    /**@brief   Assigns the packed color in RGBA order. */
    constexpr Color4b(uint32_t color) noexcept;

/**@section Public operator */
public:
    constexpr const Color4b operator+(const Color4b& rhs) const noexcept;
    constexpr const Color4b operator-(const Color4b& rhs) const noexcept;
    constexpr const Color4b operator*(const Color4b& rhs) const noexcept;
    template <typename _ValueType>
    constexpr const Color4b operator*(const _ValueType& rhs) const noexcept;
    template <typename _ValueType>
    friend constexpr const Color4b operator*(const _ValueType& lhs, const Color4b& rhs) noexcept;
    template <typename _ValueType>
    constexpr const Color4b operator/(const _ValueType& rhs) const noexcept;
    Color4b& operator+=(const Color4b& rhs) noexcept;
    Color4b& operator-=(const Color4b& rhs) noexcept;
    Color4b& operator*=(const Color4b& rhs) noexcept;
    template <typename _ValueType>
    Color4b& operator*=(const _ValueType& rhs) noexcept;
    Color4b& operator/=(const Color4b& rhs) noexcept;
    template <typename _ValueType>
    Color4b& operator/=(const _ValueType& rhs) noexcept;
    constexpr bool operator==(const Color4b& rhs) const noexcept;
    constexpr bool operator!=(const Color4b& rhs) const noexcept;
    constexpr operator uint32_t() const noexcept;
    
/**@section Public method */
public:
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;
    
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;
    
/**@section Public variable */
public:
    union
    {
        uint32_t color;
        struct { uint8_t r, g, b, a; };
    };
};

constexpr Color4b::Color4b() noexcept :
    Color4b(0, 0, 0, 255)
{
}

constexpr Color4b::Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

constexpr Color4b::Color4b(uint32_t color) noexcept :
    color(color)
{
}

constexpr const Color4b Color4b::operator+(const Color4b& rhs) const noexcept
{
    return Color4b(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}

constexpr const Color4b Color4b::operator-(const Color4b& rhs) const noexcept
{
    return Color4b(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}

constexpr const Color4b Color4b::operator*(const Color4b& rhs) const noexcept
{
    return Color4b(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
}
    
template <typename _ValueType>
constexpr const Color4b Color4b::operator*(const _ValueType& rhs) const noexcept
{
    return Color4b(r * rhs, g * rhs, b * rhs, a * rhs);
}

template <typename _ValueType>
constexpr const Color4b operator*(const _ValueType& lhs, const Color4b& rhs) noexcept
{
    return Color4b(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a);
}

template <typename _ValueType>
constexpr const Color4b Color4b::operator/(const _ValueType& rhs) const noexcept
{
    return Color4b(r / rhs, g / rhs, b / rhs, a / rhs);
}

inline Color4b& Color4b::operator+=(const Color4b& rhs) noexcept
{
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;

    return *this;
}

inline Color4b& Color4b::operator-=(const Color4b& rhs) noexcept
{
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;

    return *this;
}

inline Color4b& Color4b::operator*=(const Color4b& rhs) noexcept
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;

    return *this;
}

template <typename _ValueType>
inline Color4b& Color4b::operator*=(const _ValueType& rhs) noexcept
{
    r *= rhs;
    g *= rhs;
    b *= rhs;
    a *= rhs;

    return *this;
}

inline Color4b& Color4b::operator/=(const Color4b& rhs) noexcept
{
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;

    return *this;
}

template <typename _ValueType>
inline Color4b& Color4b::operator/=(const _ValueType& rhs) noexcept
{
    r /= rhs;
    g /= rhs;
    b /= rhs;
    a /= rhs;

    return *this;
}

constexpr bool Color4b::operator==(const Color4b& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

constexpr bool Color4b::operator!=(const Color4b& rhs) const noexcept
{
    return !this->Color4b::operator==(rhs);
}

constexpr Color4b::operator uint32_t() const noexcept
{
    return color;
}

template <std::size_t _StrBufferSize>
inline int32_t Color4b::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

inline int32_t Color4b::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", r, g, b, a);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", r, g, b, a);
#endif
}

struct Color3f
{
/**@section Public constructor */
public:
    constexpr Color3f() noexcept;
    constexpr Color3f(float r, float g, float b) noexcept;

/**@section Public operator */
public:
    constexpr bool operator==(const Color3f& rhs) const noexcept;
    constexpr bool operator!=(const Color3f& rhs) const noexcept;

/**@section Public method */
public:
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/**@section Public variable */
public:
    float r, g, b;
};

constexpr Color3f::Color3f() noexcept :
    Color3f(0.0f, 0.0f, 0.0f)
{
}
    
constexpr Color3f::Color3f(float r, float g, float b) noexcept :
    r(r),
    g(g),
    b(b)
{
}

constexpr bool Color3f::operator==(const Color3f& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b;
}

constexpr bool Color3f::operator!=(const Color3f& rhs) const noexcept
{
    return !this->operator==(rhs);
}

template <std::size_t _StrBufferSize>
inline int32_t Color3f::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

inline int32_t Color3f::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", r, g, b);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f", r, g, b);
#endif
}

struct Color4f
{
/**@section Public constructor */
public:
    constexpr Color4f() noexcept;
    constexpr Color4f(float r, float g, float b, float a) noexcept;

/**@section Public operator */
public:
    constexpr bool operator==(const Color4f& rhs) const noexcept;
    constexpr bool operator!=(const Color4f& rhs) const noexcept;

/**@section Public method */
public:
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/**@section Public variable */
public:
    float r, g, b, a;
};

constexpr Color4f::Color4f() noexcept :
    Color4f(0.0f, 0.0f, 0.0f, 1.0f)
{
}
    
constexpr Color4f::Color4f(float r, float g, float b, float a) noexcept :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

constexpr bool Color4f::operator==(const Color4f& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

constexpr bool Color4f::operator!=(const Color4f& rhs) const noexcept
{
    return !this->operator==(rhs);
}

template <std::size_t _StrBufferSize>
inline int32_t Color4f::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

inline int32_t Color4f::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#endif
}

} /* namespace tgon */
