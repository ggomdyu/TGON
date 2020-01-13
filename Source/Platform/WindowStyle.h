/**
 * @file    WindowStyle.h
 * @author  ggomdyu
 * @since   01/04/2020
 */

#pragma once
#include <cstdint>
#include <string>

namespace tgon
{

struct WindowStyle final
{
    std::string title = u8"Hello world!";
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 838;
    int32_t height = 441;
    bool hasCaption = true;
    bool enableSystemButton = true;
    bool enableFullScreen = false;
    bool resizeable = false;
    bool topMost = false;
    bool showMiddle = true;
};

} /* namespace tgon */
