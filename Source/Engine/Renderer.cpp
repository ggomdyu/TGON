#include "PrecompiledHeader.h"

#include "Renderer.h"

namespace tg
{

Renderer::Renderer(void* nativeWindow, const VideoMode& videoMode) :
    m_graphics(nativeWindow, videoMode)
{
}

void Renderer::Update()
{
}

}
