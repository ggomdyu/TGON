#include "PrecompiledHeader.h"

#include "GraphicsModule.h"
#include "../Render/MeshUtility.h"
#include "Core/File/Path.h"
#include "Core/Utility/Stopwatch.h"
#include "Core/Debug/Log.h"

namespace tgon
{

GraphicsModule::GraphicsModule(Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    m_graphics.SetClearColor(videoMode.clearColor);
    m_graphics.SetCullMode(CullMode::CW);
    m_graphics.EnableDepthTest();
    m_graphics.EnableBlend();
    m_graphics.SetBlendMode(BlendMode::Alpha);

    window.OnWindowResize += [&](int32_t width, int32_t height)
    {
        m_graphics.SetViewport(0, 0, width, height);
    };
}
    
void GraphicsModule::Update()
{
    this->Draw();
}

void GraphicsModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_renderStage.Draw(m_graphics);
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
    
RenderStage& GraphicsModule::GetRenderStage() noexcept
{
    return m_renderStage;
}

const RenderStage& GraphicsModule::GetRenderStage() const noexcept
{
    return m_renderStage;
}
    
} /* namespace tgon */
