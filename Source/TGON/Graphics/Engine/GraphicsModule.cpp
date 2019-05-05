#include "PrecompiledHeader.h"

#include "Graphics/LowLevel/ShaderProgram.h"
#include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/FVF.h"

#include "../Render/MeshUtility.h"

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const std::shared_ptr<Window>& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    auto windowSize = window->GetSize();
    m_graphics.SetViewport(0, 0, windowSize.width, windowSize.height);
    m_graphics.SetClearColor(videoMode.clearColor);
    m_graphics.SetCullMode(CullMode::CW);
    m_graphics.EnableDepthTest();
    m_graphics.EnableBlend();
    m_graphics.SetBlendMode(BlendMode::Alpha);
}
    
void GraphicsModule::Update()
{
    this->Draw();
}
    
View& GraphicsModule::GetView() noexcept
{
    return m_view;
}

const View& GraphicsModule::GetView() const noexcept
{
    return m_view;
}

void GraphicsModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_view.Draw(m_graphics);
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

} /* namespace tgon */
