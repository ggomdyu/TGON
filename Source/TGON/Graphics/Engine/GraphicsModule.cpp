#include "PrecompiledHeader.h"

#include "GraphicsModule.h"

#include "../Render/MeshUtility.h"

#include "Graphics/LowLevel/Shader.h"
#include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/FVF.h"

#include <glm/glm/matrix.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>

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
    Vector3 position[] = {
        Vector3(-100.0f, -100.0f, 0.0f),
        Vector3(-100.0f, 100.0f, 0.0f),
        Vector3(100.0f, 100.0f, 0.0f),
        Vector3(100.0f, -100.0f, 0.0f),
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    std::initializer_list<VertexBufferLayoutDescriptor> vertexBufferLayoutDescs =
    {
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(Vector3), 0),
    };

    VertexBuffer vb(position, false, vertexBufferLayoutDescs);
    IndexBuffer ib(indices, false);
    Shader shader(g_positionColorVert, g_positionColorFrag);
    static Camera camera({-960.0f / 2, 960.0f / 2, -540.0f / 2, 540.0f / 2}, -1.0f, 1.0f);

    m_graphics.ClearColorDepthBuffer();
    {
        vb.Use();
        ib.Use();
        shader.Use();
        
        shader.SetParameter4f("g_uColor", 1.0f, 0.0f, 0.0f, 1.0f);
        shader.SetParameterMatrix4fv("g_uWVP", &camera.GetViewProjectionMatrix()[0][0]);

        m_graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);

        //m_renderStage.Draw(m_graphics);
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
