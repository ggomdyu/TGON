#include "PrecompiledHeader.h"

#include "Core/Platform/Window.h"

#include "Renderer.h"

namespace tgon
{

Renderer::Renderer(const Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
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
