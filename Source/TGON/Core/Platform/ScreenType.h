/**
 * @filename    ScreenType.h
 * @author      ggomdyu
 * @since       09/16/2017
 */

#pragma once
#include <cstdint>

namespace tgon
{
namespace core
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
    constexpr Screen(int32_t width, int32_t height, int16_t bitsPerPixel, int16_t refreshRate, ScreenOrientation orientation, bool isPrimary) noexcept;

public:
    int32_t width;
    int32_t height;
    int16_t bitsPerPixel;
    int16_t refreshRate;
    ScreenOrientation orientation; // reserved
    bool isPrimary; // reserved
};

constexpr Screen::Screen(int32_t width, int32_t height, int16_t bitsPerPixel, int16_t refreshRate, ScreenOrientation orientation, bool isPrimary) noexcept :
    width(width),
    height(height),
    bitsPerPixel(bitsPerPixel),
    refreshRate(refreshRate),
    orientation(orientation),
    isPrimary(isPrimary)
{
}

} /* namespace core */
} /* namespace tgon */
