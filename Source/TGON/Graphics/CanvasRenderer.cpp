#include "PrecompiledHeader.h"

#include "Diagnostics/Log.h"
#include "Math/Matrix4x4.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/FVF.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"
#include "Graphics/CanvasSprite.h"
#include "Graphics/CanvasSpriteBatch.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Graphics/Graphics.h"

#include "CanvasRenderer.h"
#include "VertexBufferType.h"

namespace tgon
{
    
CanvasRenderer::CanvasRenderer() :
    m_spriteVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
    }),
    m_renderTarget({Application::GetInstance()->GetRootWindow()->GetExtent(), 24})
{
    this->PrepareDefaultMaterials();
}

void CanvasRenderer::Update()
{
    m_spriteVertexBuffer.Use();
    m_spriteVertexBuffer.SetData(m_spriteVertices.data(), m_spriteVertices.size() * sizeof(m_spriteVertices[0]), false);
}

void CanvasRenderer::Draw(Graphics& graphics)
{
#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Log(LogLevel::Debug, "CanvasRenderer has no camera but trying to draw.\n");
    }
#endif
    
    m_renderTarget.Use();
    
    this->FlushSpriteBatches(graphics);
    
    m_renderTarget.Unuse();
    
    graphics.SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});
    graphics.ClearColorDepthBuffer();
    
    m_uiMaterial->GetShaderProgram().SetParameterWVPMatrix4fv(m_cameraList[0]->GetViewProjectionMatrix()[0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CanvasRenderer::AddSpritePrimitive(const std::shared_ptr<CanvasSprite>& sprite, const Matrix4x4& matWorld)
{
    if (m_spriteBatches.empty())
    {
        m_spriteBatches.push_back(CanvasSpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), 0));
    }
    else if (m_spriteBatches.back().CanBatch(*sprite) == false)
    {
        m_spriteBatches.push_back(CanvasSpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), static_cast<int32_t>(m_spriteVertices.size())));
    }

    m_spriteBatches.back().Merge(*sprite, matWorld, &m_spriteVertices);
}

void CanvasRenderer::PrepareDefaultMaterials()
{
    m_uiMaterial = std::make_shared<Material>(g_positionUVVert, g_positionUVFrag);
}

void CanvasRenderer::FlushSpriteBatches(Graphics& graphics)
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

void CanvasRenderer::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool CanvasRenderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
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
