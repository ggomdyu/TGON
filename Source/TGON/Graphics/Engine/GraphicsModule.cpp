#include "PrecompiledHeader.h"

#include "Graphics/LowLevel/Shader.h"
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

    /*window.OnWindowResize += [&](int32_t width, int32_t height)
    {
        m_graphics.SetViewport(0, 0, width, height);

        auto& cameraList = m_View.GetCameraList();
        for (auto& camera : cameraList)
        {
            float halfWidth = static_cast<float>(width) * 0.5f;
            float halfHeight = static_cast<float>(height) * 0.5f;
            camera->SetOrthoPlane({ -halfWidth, halfWidth, -halfHeight, halfHeight });
        }
    };*/
}
    
void GraphicsModule::Update()
{
    this->Draw();
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
    
View& GraphicsModule::GetView() noexcept
{
    return m_view;
}

const View& GraphicsModule::GetView() const noexcept
{
    return m_view;
}
    
} /* namespace tgon */
