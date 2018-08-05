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
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Normal blend
//    glBlendFunc(GL_ONE, GL_ZERO);
//    glBlendEquation(GL_FUNC_ADD);
    
    // Subtractive
//    glBlendFunc(GL_ONE, GL_ONE);
//    glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
    
    // Additive
//    glBlendFunc(GL_ONE, GL_ONE);
//    glBlendEquation(GL_FUNC_ADD);
    
    
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
    static Camera camera;
    static TextureMaterial material(std::make_shared<Texture>(GetDesktopDirectory() + "/grass.png"));
    static auto quad = MakeQuad();
    static float yRotation1 = 0.0f;
    std::vector<Matrix4x4> matWVP{
        Matrix4x4::Scale(0.4f, 0.4f, 1.0f) *
            Matrix4x4::RotateY(yRotation1) *
            Matrix4x4::Translate(-0.5f, 0.0f, 0.5f) *
            camera.GetViewProjectionMatrix(),
        Matrix4x4::Scale(0.4f, 0.4f, 1.0f) * Matrix4x4::Translate(-0.3f, 0.0f, 0.3f) * camera.GetViewProjectionMatrix(),
        Matrix4x4::Scale(0.4f, 0.4f, 1.0f) * Matrix4x4::Translate(0.4f, 0.0f, 0.1f) * camera.GetViewProjectionMatrix()
    };
    
    yRotation1 += 0.01f;
    
    auto& eyePt = camera.GetEyePt();
    
    std::sort(matWVP.begin(), matWVP.end(), [&](const Matrix4x4& first, const Matrix4x4& second)
    {
        float length1 = Vector3(eyePt - Vector3(first.m30, first.m31, first.m32)).Length();
        float length2 = Vector3(eyePt - Vector3(second.m30, second.m31, second.m32)).Length();
        
        return length1 < length2;
    });
    
    m_graphics.ClearColorDepthBuffer();
    {
        material.Use();
       
        quad->GetVertexBuffer()->Use();
        quad->GetIndexBuffer()->Use();

        material.GetShader()->SetParameterMatrix4fv("g_uMVP", matWVP[0][0]);
        m_graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
        
        material.GetShader()->SetParameterMatrix4fv("g_uMVP", matWVP[1][0]);
        m_graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
//
        material.GetShader()->SetParameterMatrix4fv("g_uMVP", matWVP[2][0]);
        m_graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
//
//        m_batchGroup.Draw(m_graphics);
    }
    m_graphics.SwapBuffer();
}
    
void GraphicsModule::AddCamera(const Camera& camera)
{
    m_cameraList.push_back(camera);
}

std::vector<Camera>& GraphicsModule::GetCameraList() noexcept
{
    return m_cameraList;
}
    
const std::vector<Camera>& GraphicsModule::GetCameraList() const noexcept
{
    return m_cameraList;
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
