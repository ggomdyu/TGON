/**
 * @file    EngineConfig.h
 * @author  ggomdyu
 * @since   01/04/2020
 */

#pragma once
#include "Graphics/VideoMode.h"
#include "Platform/WindowStyle.h"

#include "InputMode.h"

namespace tgon
{

struct EngineConfig final
{
    WindowStyle windowStyle;
    InputMode inputMode;
    VideoMode videoMode;
};

} /* namespace tgon */
