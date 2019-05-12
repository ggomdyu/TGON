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
    std::string title = u8"Hello World!";

    int32_t x = 100;
    int32_t y = 100;
    int32_t width = 1200;
    int32_t height = 1200;

    bool hasCaption = true;
    bool enableSystemButton = true;
    bool enableFullScreen = false;
    bool resizeable = true;
    bool topMost = false;
    bool showMiddle = false;
};

} /* namespace tgon */
