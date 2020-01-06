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
/**@section Constructor */
public:
    explicit EngineConfig(const WindowStyle& windowStyle);
    EngineConfig(const WindowStyle& windowStyle, const InputMode& inputMode, const VideoMode& videoMode);

/**@section Variable */
public:
    WindowStyle windowStyle {};
    InputMode inputMode {};
    VideoMode videoMode {};
};

inline EngineConfig::EngineConfig(const WindowStyle& windowStyle) :
    windowStyle(windowStyle)
{
}

inline EngineConfig::EngineConfig(const WindowStyle& windowStyle, const InputMode& inputMode, const VideoMode& videoMode) :
    windowStyle(windowStyle),
    inputMode(inputMode),
    videoMode(videoMode)
{
}

} /* namespace tgon */
