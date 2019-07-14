#include "PrecompiledHeader.h"

#include "Diagnostics/Log.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/FVF.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Graphics/Graphics.h"
#include "Graphics/VertexBufferType.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"
#include "UI/CanvasSprite.h"
#include "UI/CanvasSpriteBatch.h"

#include "UIRenderer.h"

//todo:remove below headers
#include "Platform/Window.h"

namespace tgon
{
    
UIRenderer::UIRenderer() :
    m_spriteVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
    }),
    m_quadVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
    }),
    m_renderTarget({Application::GetInstance()->GetRootWindow()->GetExtent(), 24})
{   
    this->PrepareDefaultMaterials();
}

void UIRenderer::Update()
{
    m_spriteVertexBuffer.Use();
    m_spriteVertexBuffer.SetData(m_spriteVertices.data(), m_spriteVertices.size() * sizeof(m_spriteVertices[0]), false);
}

void UIRenderer::Draw(Graphics& graphics)
{
#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Log(LogLevel::Debug, "CanvasRenderer has no camera but trying to draw.\n");
        return;
    }
#endif
    
    this->FlushSpriteBatches(graphics);
}
    
void UIRenderer::DebugRenderTargetDraw(Graphics& graphics)
{
    // Use custom framebuffer
    m_renderTarget.Use();
    {
        m_uiMaterial->Use();
        m_spriteVertexBuffer.Use();
        
        graphics.SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});
        graphics.ClearColorDepthBuffer();
        
        this->FlushSpriteBatches(graphics);
    }
    
    // Use default framebuffer
    m_renderTarget.Unuse();
    {
        m_inverseMaterial->Use();
        m_inverseMaterial->GetShaderProgram().SetParameterWVPMatrix4fv(m_cameraList[0]->GetViewProjectionMatrix()[0]);
        m_quadVertexBuffer.Use();
        
        graphics.SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
        graphics.ClearColorDepthBuffer();

        graphics.DrawPrimitives(PrimitiveType::Triangles, 0, 6);
    }
}

void UIRenderer::AddSpritePrimitive(const std::shared_ptr<Sprite>& sprite, const Matrix4x4& matWorld)
{
    if (m_spriteBatches.empty())
    {
        m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), 0));
    }
    else if (m_spriteBatches.back().CanBatch(*sprite) == false)
    {
        m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), static_cast<int32_t>(m_spriteVertices.size())));
    }

    m_spriteBatches.back().Merge(*sprite, matWorld, &m_spriteVertices);
}

void UIRenderer::PrepareDefaultMaterials()
{
    m_uiMaterial = std::make_shared<Material>(g_positionUVVert, g_positionUVFrag);
    m_inverseMaterial = std::make_shared<Material>(g_positionUVVert, g_sharpenFrag);
}

void UIRenderer::FlushSpriteBatches(Graphics& graphics)
{
    m_uiMaterial->Use();
    
    for (auto& camera : m_cameraList)
    {
        m_uiMaterial->GetShaderProgram().SetParameterWVPMatrix4fv(camera->GetViewProjectionMatrix()[0]);
        
        for (auto& spriteBatch : m_spriteBatches)
        {
            spriteBatch.FlushBatch(graphics);
        }
    }

    m_spriteBatches.clear();
    m_spriteVertices.clear();
}

void UIRenderer::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool UIRenderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& item)
    {
        return item == camera;
    });
    if (iter == m_cameraList.end())
    {
        return false;
    }
    
    m_cameraList.erase(iter);
    return true;
}

} /* namespace tgon */
