/**
 * @filename    Color.h
 * @author      ggomdyu
 * @since       05/03/2017
 */

#pragma once
#include <cstdint>
#include <cstdio>

namespace tgon
{
namespace math
{

struct Color4b
{
/* @section Public constructor */
public:
    constexpr Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;

    /* @brief   Assigns packed color in RGBA order. */
    constexpr Color4b(uint32_t color) noexcept;

/* @section Public operator */
public:
    constexpr operator uint32_t() const noexcept;

/* @section Public method */
public:
    /**
     * @brief                   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return                  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief                       Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/* @section Public variable */
public:
    union
    {
        uint32_t color;
        struct { uint8_t r, g, b, a; };
    };
};

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

constexpr Color4b::operator uint32_t() const noexcept
{
    return color;
}

template <typename _ValueType>
template <std::size_t _StrBufferSize>
inline int32_t Color4b::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

template <typename _ValueType>
inline int32_t Color4b::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%d %d %d %d", r, g, b, a);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize , "%d %d %d %d", r, g, b, a);
#endif
}

struct Color4f
{
/* @section Public constructor */
public:
    constexpr Color4f(float r, float g, float b, float a) noexcept;

/* @section Public method */
public:
    /**
     * @brief                   Converts color to a string.
     * @param [out] destStr     The destination of the string to be written.
     * @return                  The length of string converted.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief                       Converts color to a string.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The size of destStr.
     * @return                      The length of string converted.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

    /* @section Public variable */
public:
    float r, g, b, a;
};

constexpr Color4f::Color4f(float r, float g, float b,float a) noexcept :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

template <typename _ValueType>
template <std::size_t _StrBufferSize>
inline int32_t Color4f::ToString(char(&destStr)[_StrBufferSize]) const
{
    return this->ToString(destStr, _StrBufferSize);
}

template <typename _ValueType>
inline int32_t Color4f::ToString(char* destStr, std::size_t strBufferSize) const
{
#if _MSC_VER
    return sprintf_s(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#else
    return snprintf(destStr, sizeof(destStr[0]) * strBufferSize, "%f %f %f %f", r, g, b, a);
#endif
}

} /* namespace math */
} /* namespace tgon */
