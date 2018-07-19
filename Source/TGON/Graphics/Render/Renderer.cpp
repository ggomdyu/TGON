#include "PrecompiledHeader.h"

#include "Core/Platform/Window.h"

#include "Renderer.h"

namespace tgon
{

Renderer::Renderer(const Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
}
    
void Renderer::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_spriteBatch.FlushBatch(m_graphics);
    }
    m_graphics.SwapBuffer();
}
    
SpriteBatch& Renderer::GetSpriteBatch() noexcept
{
    return m_spriteBatch;
}
    
const SpriteBatch& Renderer::GetSpriteBatch() const noexcept
{
    return m_spriteBatch;
}

Graphics& Renderer::GetGraphics() noexcept
{
    return m_graphics;
}

const Graphics& Renderer::GetGraphics() const noexcept
{
    return m_graphics;
}
    
} /* namespace tgon */
