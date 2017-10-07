/**
 * @filename    RenderWindow.hpp
 * @author      ggomdyu
 * @since       09/28/2017
 * @brief
 */

#pragma once
#include "Core/Platform/Window.h"

namespace tgon
{
namespace graphics
{

class TGON_API GraphicsWindow :
    public platform::Window
{
/* @section Public constructor */
public:
    GraphicsWindow();
    virtual ~GraphicsWindow() = default;

/* @section Private variable */
private:
};

} /* namespace platform */
} /* namespace tgon */
