#include "PrecompiledHeader.h"

#include "Renderer.h"

namespace tgon
{

Renderer::Renderer(const Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
}

} /* namespace tgon */
