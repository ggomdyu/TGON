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
/* @section Public constructor */
public:
    /* @brief   Assigns all components to zero. */
    constexpr Color4b() noexcept :
        r(0),
        g(0),
        b(0),
        a(0)
    {
    }

    /* @brief   Assigns color components with the specified value. */
    constexpr Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept :
        r(r),
        g(g),
        b(b),
        a(a)
    {
    }

    /* @brief   Assigns the packed color in RGBA order. */
    constexpr Color4b(uint32_t color) noexcept :
        color(color)
    {
    }

/* @section Public operator */
public:
    constexpr const Color4b operator+(const Color4b& rhs) const noexcept
    {
        return Color4b(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
    }

    constexpr const Color4b operator-(const Color4b& rhs) const noexcept
    {
        return Color4b(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
    }

    constexpr const Color4b operator*(const Color4b& rhs) const noexcept
    {
        return Color4b(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
    }
    
    template <typename _ValueType>
    constexpr const Color4b operator*(const _ValueType& rhs) const noexcept
    {
        return Color4b(r * rhs, g * rhs, b * rhs, a * rhs);
    }

    template <typename _ValueType>
    friend constexpr const Color4b operator*(const _ValueType& lhs, const Color4b& rhs) noexcept
    {
        return Color4b(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a);
    }

    template <typename _ValueType>
    constexpr const Color4b operator/(const _ValueType& rhs) const noexcept
    {
        return Color4b(r / rhs, g / rhs, b / rhs, a / rhs);
    }

    Color4b& operator+=(const Color4b& rhs) noexcept
    {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;

        return *this;
    }

    Color4b& operator-=(const Color4b& rhs) noexcept
    {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        a -= rhs.a;

        return *this;
    }

    Color4b& operator*=(const Color4b& rhs) noexcept
    {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        a *= rhs.a;

        return *this;
    }

    template <typename _ValueType>
    Color4b& operator*=(const _ValueType& rhs) noexcept
    {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        a *= rhs;

        return *this;
    }

    Color4b& operator/=(const Color4b& rhs) noexcept
    {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        a /= rhs.a;

        return *this;
    }

    template <typename _ValueType>
    Color4b& operator/=(const _ValueType& rhs) noexcept
    {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        a /= rhs;

        return *this;
    }

    constexpr bool operator==(const Color4b& rhs) const noexcept
    {
        return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
    }

    constexpr bool operator!=(const Color4b& rhs) const noexcept
    {
        return !this->operator==(rhs);
    }

    constexpr operator uint32_t() const noexcept
    {
        return color;
    }

/* @section Public method */
public:
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const
    {
        return this->ToString(destStr, _StrBufferSize);
    }

    /**
     * @brief   Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const
    {
#if _MSC_VER
        return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", r, g, b, a);
#else
        return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", r, g, b, a);
#endif
    }

/* @section Public variable */
public:
    union
    {
        uint32_t color;
        struct { uint8_t r, g, b, a; };
    };
};

struct Color4f
{
/* @section Public constructor */
public:
    constexpr Color4f() noexcept :
        r(0.0f),
        g(0.0f),
        b(0.0f),
        a(0.0f)
    {
    }
    
    constexpr Color4f(float r, float g, float b, float a) noexcept :
        r(r),
        g(g),
        b(b),
        a(a)
    {
    }

/* @section Public operator */
public:
    constexpr bool operator==(const Color4f& rhs) const noexcept
    {
        return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
    }

    constexpr bool operator!=(const Color4f& rhs) const noexcept
    {
        return !this->operator==(rhs);
    }

/* @section Public method */
public:
    /**
     * @brief   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const
    {
        return this->ToString(destStr, _StrBufferSize);
    }

    /**
     * @brief   Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return  The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const
    {
#if _MSC_VER
        return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#else
        return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#endif
    }

/* @section Public variable */
public:
    float r, g, b, a;
};

} /* namespace tgon */
