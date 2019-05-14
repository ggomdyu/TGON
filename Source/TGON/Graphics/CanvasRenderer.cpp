#include "PrecompiledHeader.h"

#include "Diagnostics/Log.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/FVF.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"
#include "Graphics/CanvasSprite.h"
#include "Graphics/CanvasSpriteBatch.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Graphics/Graphics.h"

#include "CanvasRenderer.h"

namespace tgon
{
    
CanvasRenderer::CanvasRenderer() :
    m_spriteVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
    })
{
    this->PrepareDefaultMaterials();
}

void CanvasRenderer::Update()
{
    m_spriteBatches.clear();
    m_spriteVertices.clear();
    
    for (const auto& sprite : m_sprites)
    {
        if (m_spriteBatches.empty())
        {
            m_spriteBatches.push_back(CanvasSpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), 0));
        }
        else if (m_spriteBatches.back().CanBatch(*sprite) == false)
        {
            m_spriteBatches.push_back(CanvasSpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), static_cast<int32_t>(m_spriteVertices.size())));
        }
        
        m_spriteBatches.back().Merge(*sprite, &m_spriteVertices);
    }
    
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
    
    this->FlushSpriteBatches(graphics);
}

void CanvasRenderer::AddSprite(const std::shared_ptr<CanvasSprite>& sprite)
{
    m_sprites.push_back(sprite);
}

bool CanvasRenderer::RemoveSprite(const std::shared_ptr<CanvasSprite>& sprite)
{
    auto iter = std::find_if(m_sprites.begin(), m_sprites.end(), [&](const std::shared_ptr<CanvasSprite>& item) {
        return item == sprite;
    });
    if (iter == m_sprites.end())
    {
        return false;
    }
    
    m_sprites.erase(iter);
    return true;
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
        m_uiMaterial->GetShaderProgram().SetParameterMatrix4fv("g_uWVP", camera->GetViewProjectionMatrix()[0]);
        
        for (auto& spriteBatch : m_spriteBatches)
        {
            spriteBatch.FlushBatch(graphics);
        }
    }
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
