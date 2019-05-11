#include "PrecompiledHeader.h"

#include "SpriteBatch.h"
#include "Texture.h"
#include "Graphics.h"
#include "Material.h"
#include "Sprite.h"
#include "FVF.h"
#include "MeshUtility.h"

namespace tgon
{

SpriteBatch::SpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, const FRect& textureRect) noexcept :
    m_texture(texture),
    m_blendMode(blendMode),
    m_enableScissorRect(enableScissorRect),
    m_scissorRect(scissorRect),
    m_vertexStartOffset(0),
    m_vertexEndOffset(0)
{
}

bool SpriteBatch::CanBatch(const Sprite& rhs) const noexcept
{
    if (m_texture == rhs.GetTexture() &&
        m_blendMode == rhs.GetBlendMode() &&
        m_enableScissorRect == rhs.IsEnableScissorRect() &&
        m_scissorRect == rhs.GetScissorRect())
    {
        return true;
    }
    
    return false;
}
    
void SpriteBatch::FlushBatch(Graphics& graphics)
{
    m_texture->Use();
    
    if (m_enableScissorRect)
    {
        graphics.EnableScissorTest();
        graphics.SetScissorRect(m_scissorRect);
    }
    else
    {
        graphics.DisableScissorTest();
    }
    
    graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 6);
}
    
void SpriteBatch::Merge(const Sprite& rhs)
{
//    if (this->CanBatch(rhs) == false)
//    {
//        return;
//    }
//    
//    const auto& textureRect = rhs.GetTextureRect();
//    const auto& textureSize = rhs.GetTexture()->GetSize();
//    auto leftUV = textureRect.x / textureSize.width;
//    auto topUV = textureRect.y / textureSize.height;
//    auto rightUV = textureRect.width / textureSize.width;
//    auto bottomUV = textureRect.height / textureSize.height;
//
//    auto halfWidth = textureRect.width / 2;
//    auto halfHeight = textureRect.height / 2;
//
////    float* vertices = &m_vertices[m_vertices.size()];
////    m_vertices.resize(m_vertices.size() + (sizeof(V3F_T2F) / sizeof(float)) * 4);
//    
//    m_vertices[0] = -halfWidth;
//    m_vertices[1] = halfHeight;
//    m_vertices[2] = 0.0f;
//    m_vertices[3] = leftUV;
//    m_vertices[4] = topUV;
//    
//    m_vertices[5] = halfWidth;
//    m_vertices[6] = halfHeight;
//    m_vertices[7] = 0.0f;
//    m_vertices[8] = rightUV;
//    m_vertices[9] = topUV;
//    
//    m_vertices[10] = halfWidth;
//    m_vertices[11] = -halfHeight;
//    m_vertices[12] = 0.0f;
//    m_vertices[13] = rightUV;
//    m_vertices[14] = bottomUV;
//
//    m_vertexBuffer.SetData(&m_vertices[0], m_vertices.size() * sizeof(float), true, {
//        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, 0, 0),
//        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, true, 0, 12),
//    });
    
//    g_sharedVertices[15] = -halfWidth;
//    g_sharedVertices[16] = -halfHeight;
//    g_sharedVertices[17] = 0.0f;
//    g_sharedVertices[18] = leftUV;
//    g_sharedVertices[19] = bottomUV;
    
    auto triangle = MeshUtility::GetSharedTriangle();
    triangle->Use();
}

//void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
//{
//    (*m_material)->Use();
//
//    for (const auto& matWorld : m_matWorlds)
//    {
//        (*m_material)->SetWVP((*matWorld) * camera.GetViewProjectionMatrix());
//
//        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
//    }
//}
//
//std::shared_ptr<Sprite> SpriteBatch::GetSprite() noexcept
//{
//    return *m_sprite;
//}
//    
//std::shared_ptr<const Sprite> SpriteBatch::GetSprite() const noexcept
//{
//    return *m_sprite;
//}
//
//std::shared_ptr<Material> SpriteBatch::GetMaterial() noexcept
//{
//    return *m_material;
//}
//    
//std::shared_ptr<const Material> SpriteBatch::GetMaterial() const noexcept
//{
//    return *m_material;
//}
//    
} /* namespace tgon */
