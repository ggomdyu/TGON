/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <memory>

#include "Core/Object/DelegateChain.h"

#include "../LowLevel/Graphics.h"
#include "SpriteBatch.h"

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
    void Draw();
    
    SpriteBatch& GetSpriteBatch() noexcept;
    
    const SpriteBatch& GetSpriteBatch() const noexcept;
    
    Graphics& GetGraphics() noexcept;
    
    const Graphics& GetGraphics() const noexcept;
    
/* @section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnWindowResize;

/* @section Private method */
private:
    
/* @section Private variable */
public:
    SpriteBatch m_spriteBatch;
    Graphics m_graphics;
};

} /* namespace tgon */
