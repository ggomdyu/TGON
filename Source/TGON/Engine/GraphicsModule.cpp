#include "PrecompiledHeader.h"

#include "Graphics/FVF.h"
#include "Platform/Window.h"

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    auto windowSize = window.GetExtent();
    m_graphics.SetViewport(0, 0, windowSize.width, windowSize.height);
    m_graphics.SetClearColor(videoMode.clearColor);
    m_graphics.SetCullMode(CullMode::CW);
    m_graphics.EnableDepthTest();
    m_graphics.EnableBlend();
    m_graphics.SetBlendMode(BlendMode::Alpha);
}
    
void GraphicsModule::Update()
{
    m_meshRenderer.Update();
    m_uiRenderer.Update();
    
    this->Draw();
}

void GraphicsModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_meshRenderer.Draw(m_graphics);
        m_uiRenderer.Draw(m_graphics);
    }
    m_graphics.SwapBuffer();
}
    
Graphics& GraphicsModule::GetGraphics() noexcept
{
    return m_graphics;
}

const Graphics& GraphicsModule::GetGraphics() const noexcept
{
    return m_graphics;
}
    
UIRenderer& GraphicsModule::GetUIRenderer() noexcept
{
    return m_uiRenderer;
}

const UIRenderer& GraphicsModule::GetUIRenderer() const noexcept
{
    return m_uiRenderer;
}

MeshRenderer& GraphicsModule::GetMeshRenderer() noexcept
{
    return m_meshRenderer;
}
    
const MeshRenderer& GraphicsModule::GetMeshRenderer() const noexcept
{
    return m_meshRenderer;
}

} /* namespace tgon */
