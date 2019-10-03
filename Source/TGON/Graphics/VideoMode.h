/**
 * @file    VideoMode.h
 * @author  ggomdyu
 * @since   10/03/2019
 */

#pragma once
#include "Math/Color.h"

namespace tgon
{

struct VideoMode final
{
    Color4f clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
    bool enableHardwareAccelerate = true;
    bool enableTripleBuffer = false;
    bool enableVerticalSync = false;
    bool enableMultiSampling = false;
    uint16_t sampleCount = 16;
    uint16_t colorBits = 32;
    uint16_t depthBits;
    uint16_t stencilBits;
};

} /* namespace tgon */
