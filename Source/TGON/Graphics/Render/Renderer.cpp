#include "PrecompiledHeader.h"

#include "Core/Platform/Window.h"

#include "Renderer.h"

namespace tgon
{

Renderer::Renderer(Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    window.OnWindowResize += [&](int32_t width, int32_t height)
    {
        this->OnWindowResize(width, height);
    };
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
