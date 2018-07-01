/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <memory>

#include "Core/Object/Delegate.h"

#include "../LowLevel/Graphics.h"

namespace tgon
{
    
class Graphics;
class Window;
struct VideoMode;

class Renderer final
{
/* @section Public constructor */
public:
    Renderer(const Window& window, const VideoMode& videoMode);

/* @section Public method */
public:
    Delegate<void()> OnWindowResize;

/* @section Private method */
private:
    
/* @section Private variable */
public:
    Graphics m_graphics;
};

} /* namespace tgon */
