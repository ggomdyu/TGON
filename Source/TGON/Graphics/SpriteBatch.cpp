#include "PrecompiledHeader.h"

#include "SpriteBatch.h"
#include "Texture.h"
#include "Graphics.h"
#include "Material.h"
#include "Sprite.h"
#include "FVF.h"
#include "MeshUtility.h"
#include "Random/Random.h"

namespace tgon
{
    
SpriteBatch::SpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, const FRect& textureRect, int32_t vertexStartOffset) noexcept :
    m_texture(texture),
    m_blendMode(blendMode),
    m_enableScissorRect(enableScissorRect),
    m_scissorRect(scissorRect),
    m_vertexStartOffset(vertexStartOffset),
    m_vertexEndOffset(vertexStartOffset)
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
    
    graphics.DrawPrimitives(PrimitiveType::Triangles, m_vertexStartOffset / sizeof(V3F_T2F), (m_vertexEndOffset - m_vertexStartOffset) / (sizeof(V3F_T2F) / 4));
}
    
bool SpriteBatch::Merge(const Sprite& rhs, std::vector<float>* vertices)
{
    const auto& textureRect = rhs.GetTextureRect();
    const auto& textureSize = rhs.GetTexture()->GetSize();
    float leftUV = textureRect.x / textureSize.width;
    float topUV = textureRect.height / textureSize.height;
    float rightUV = textureRect.width / textureSize.width;
    float bottomUV = textureRect.y / textureSize.height;
    float halfWidth = textureRect.width / 2;
    float halfHeight = textureRect.height / 2;

    auto oldVertexEndOffset = m_vertexEndOffset;
    auto expandSize = sizeof(V3F_T2F) / 4 * 6;
    vertices->resize(m_vertexEndOffset + expandSize);
    m_vertexEndOffset += expandSize;

    auto x = RandRange(-200.0f, 200.0f);

   // Left top
    float* newVertices = &(*vertices)[oldVertexEndOffset];
    newVertices[0] = -halfWidth + x;
    newVertices[1] = halfHeight;
    newVertices[2] = 0.0f;
    newVertices[3] = leftUV;
    newVertices[4] = topUV;

    // Right top
    newVertices[5] = halfWidth + x;
    newVertices[6] = halfHeight;
    newVertices[7] = 0.0f;
    newVertices[8] = rightUV;
    newVertices[9] = topUV;
    
    // Right bottom
    newVertices[10] = halfWidth + x;
    newVertices[11] = -halfHeight;
    newVertices[12] = 0.0f;
    newVertices[13] = rightUV;
    newVertices[14] = bottomUV;
    
    // Right bottom
    newVertices[15] = halfWidth + x;
    newVertices[16] = -halfHeight;
    newVertices[17] = 0.0f;
    newVertices[18] = rightUV;
    newVertices[19] = bottomUV;

    // Left bottom
    newVertices[20] = -halfWidth + x;
    newVertices[21] = -halfHeight;
    newVertices[22] = 0.0f;
    newVertices[23] = leftUV;
    newVertices[24] = bottomUV;

    // Left top
    newVertices[25] = -halfWidth + x;
    newVertices[26] = halfHeight;
    newVertices[27] = 0.0f;
    newVertices[28] = leftUV;
    newVertices[29] = topUV;

    return true;
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
