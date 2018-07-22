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
        m_batchGroup.Draw(m_graphics);
    }
    m_graphics.SwapBuffer();
}

BatchGroup& Renderer::GetBatchGroup() noexcept
{
    return m_batchGroup;
}

const BatchGroup& Renderer::GetBatchGroup() const noexcept
{
    return m_batchGroup;
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
