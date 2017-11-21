/**
 * @filename    GraphicsWindow.h
 * @author      ggomdyu
 * @since       09/28/2017
 * @brief
 */

#pragma once
#include "Core/Platform/Window.h"

namespace tgon
{
namespace platform
{

class TGON_API GraphicsWindow :
    public Window
{
/* @section Public constructor */
public:
    using Window::Window;

/* @section Public destructor */
public:
    virtual ~GraphicsWindow() = default;
};

} /* namespace platform */
} /* namespace tgon */
