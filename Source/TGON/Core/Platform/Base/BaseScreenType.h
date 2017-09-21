/**
 * @filename    BaseScreenType.h
 * @author      ggomdyu
 * @since       09/16/2017
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

enum class ScreenOrientation
{
    Portrait,
    InversedPortrait,
    Landscape,
    InversedLandscape,
};

enum class ColorSpace
{
    SRGB,
    RGB,
    CMYK,
    Gray,
};

struct Screen
{
public:
    constexpr Screen(int32_t width, int32_t height, int16_t bitsPerPixel) noexcept;

public:
    int32_t width;
    int32_t height;
    int16_t bitsPerPixel;
};

constexpr Screen::Screen(int32_t width, int32_t height, int16_t bitsPerPixel) noexcept :
    width(width),
    height(height),
    bitsPerPixel(bitsPerPixel)
{
}

} /* namespace platform */
} /* namespace tgon */
