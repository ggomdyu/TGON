/**
 * @filename    Color.h
 * @author      ggomdyu
 * @since       05/03/2017
 */

#pragma once
#include <cstdint>
#include <cstdio>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace math
{

/* @brief Color structure in ARGB order. */
struct Color4b
{
/* @section Public constructor */
public:
    constexpr Color4b(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept;
    constexpr Color4b(uint32_t packedColor) noexcept;

/* @section Public operator */
public:
    constexpr operator uint32_t() const noexcept;

/* @section Public method */
public:
    constexpr uint32_t ToRGBA() const noexcept;

    // Todo: Implement ToString

/* @section Public variable */
public:
    union
    {
#ifdef TGON_USING_LITTLE_ENDIAN
        uint32_t packedColor;
        struct { uint8_t a, r, g, b; };
#else
        uint32_t packedColor;
        struct { uint8_t b, g, r, a; };
#endif
    };
};

constexpr Color4b::Color4b(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept :
    a(a),
    r(r),
    g(g),
    b(b)
{
}

constexpr Color4b::Color4b(uint32_t packedColor) noexcept :
    packedColor(packedColor)
{
}

constexpr Color4b::operator uint32_t() const noexcept
{
    return packedColor;
}

constexpr uint32_t Color4b::ToRGBA() const noexcept
{
    return (r) | (g << 8) | (b << 16) | (a << 24);
}

struct Color4f
{
};

} /* namespace math */
} /* namespace tgon */
