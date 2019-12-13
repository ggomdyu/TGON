#include "PrecompiledHeader.h"

#include "Graphics/VertexFormat.h"
#include "Platform/Window.h"

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    auto clientSize = window.GetClientSize();
    m_graphics.SetViewport(0, 0, clientSize.width, clientSize.height);
    m_graphics.SetClearColor(videoMode.clearColor);
    m_graphics.SetCullMode(CullMode::CW);
    m_graphics.EnableDepthTest();
    m_graphics.EnableBlend();
    m_graphics.SetBlendMode(BlendMode::Alpha);
    
    window.OnResize += MakeDelegate<&GraphicsModule::OnResizeWindow>(this);
}

void GraphicsModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_uiRenderer.Draw(m_graphics);
    }
    m_graphics.SwapBuffer();
}

void GraphicsModule::OnResizeWindow(int32_t width, int32_t height)
{
    m_graphics.SetViewport(0, 0, width, height);
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

void GraphicsModule::Update()
{
    m_uiRenderer.Update();
    
    this->Draw();
}

} /* namespace tgon */
