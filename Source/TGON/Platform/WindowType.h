/**
 * @file    WindowType.h
 * @author  ggomdyu
 * @since   05/05/2017
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{

struct WindowStyle final
{
    std::string title = u8"°¡³ªa";

    int32_t x = 100;
    int32_t y = 100;
    int32_t width = 600;
    int32_t height = 600;

    bool hasCaption = true;
    bool enableSystemButton = true;
    bool enableFullScreen = false;
    bool resizeable = true;
    bool topMost = false;
    bool showMiddle = true;
};

} /* namespace tgon */
