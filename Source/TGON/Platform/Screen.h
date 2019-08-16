/**
 * @file    Screen.h
 * @author  ggomdyu
 * @since   08/06/2017
 * @brief   Set of Plaform-agnostic Screen interfaces.
 */

#pragma once
#include <vector>

#include "Config.h"

namespace tgon
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

/**@brief   Returns count of detected monitors. */
TGON_API int32_t GetScreenCount();

/**@brief   Returns current primary screen information.  */
TGON_API Screen GetPrimaryScreen();

/**@brief   Returns all detected screen informations.*/
TGON_API std::vector<Screen> GetAllScreens();

}
