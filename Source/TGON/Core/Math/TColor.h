/**
 * @filename    TColor.h
 * @author   ggomdyu
 * since    05/03/2017
 */

#pragma once
#include "Core/Platform/TConfig.h"

#include <cstdint>

namespace tgon
{

/* @brief Store color in ARGB order. */
struct TColor4b
{
/**
 * @section Ctor/Dtor
 */
public:
    constexpr TColor4b(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept;
    constexpr explicit TColor4b(uint32_t packedColor);

/**
 * @section Public command method
 */
public:
    constexpr uint32_t ToRGBA() const noexcept;
    constexpr operator uint32_t() const noexcept;

/**
 * @section Public variable
 */
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

constexpr tgon::TColor4b::TColor4b(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept :
    a(a), r(r), g(g), b(b)
{
}

constexpr tgon::TColor4b::TColor4b(uint32_t packedColor) :
    packedColor(packedColor)
{
}

constexpr uint32_t tgon::TColor4b::ToRGBA() const noexcept
{
    return (r) | (g << 8) | (b << 16) | (a << 24);
}

constexpr tgon::TColor4b::operator uint32_t() const noexcept
{
    return (r) | (g << 8) | (b << 16) | (a << 24);
}

struct TColor4f
{
};


} /* namespace tgon */