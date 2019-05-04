#include "PrecompiledHeader.h"

#include "../LowLevel/Texture.h"

#include "Sprite.h"
#include "SpriteBatch.h"
#include "FVF.h"

namespace tgon
{
    
SpriteBatch::SpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, const FRect& scissorRect, const FRect& textureRect) noexcept :
    m_texture(texture),
    m_blendMode(blendMode),
    m_scissorRect(scissorRect)
{
}

bool SpriteBatch::CanBatch(const Sprite& rhs) const noexcept
{
    if (m_texture == rhs.GetTexture() &&
        m_blendMode == rhs.GetBlendMode() &&
        m_scissorRect == rhs.GetScissorRect())
    {
        return true;
    }
    
    return false;
}
    
void SpriteBatch::Merge(const Sprite& rhs)
{
    const auto& textureRect = rhs.GetTextureRect();
    const auto& textureSize = rhs.GetTexture()->GetSize();
    auto leftUV = textureRect.x / textureSize.width;
    auto topUV = textureRect.y / textureSize.height;
    auto rightUV = textureRect.width / textureSize.width;
    auto bottomUV = textureRect.height / textureSize.height;
 
    float* vertices = &m_vertices[m_vertices.size()];
    m_vertices.resize(m_vertices.size() + (sizeof(V3F_T2F) / sizeof(float)) * 4);
    
    vertices[0] = vertices[3] = leftUV;
    vertices[1] = vertices[4] = topUV;
    vertices[2] = 0.0f;
    
    vertices[5] = vertices[8] = rightUV;
    vertices[6] = vertices[9] = topUV;
    vertices[7] = 0.0f;
    
    vertices[10] = vertices[13] = rightUV;
    vertices[11] = vertices[14] = topUV;
    vertices[12] = 0.0f;
    
    vertices[15] = vertices[18] = rightUV;
    vertices[16] = vertices[19] = topUV;
    vertices[17] = 0.0f;
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
