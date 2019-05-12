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
    
    graphics.DrawPrimitives(PrimitiveType::Triangles, (m_vertexEndOffset - m_vertexStartOffset) / sizeof(V3F_T2F));
}
    
bool SpriteBatch::Merge(const Sprite& rhs, std::vector<float>* vertices)
{
    const auto& textureRect = rhs.GetTextureRect();
    const auto& textureSize = rhs.GetTexture()->GetSize();
    auto leftUV = textureRect.x / textureSize.width;
    auto topUV = textureRect.height / textureSize.height;
    auto rightUV = textureRect.width / textureSize.width;
    auto bottomUV = textureRect.y / textureSize.height;
    auto halfWidth = textureRect.width / 2;
    auto halfHeight = textureRect.height / 2;

    auto expandSize = sizeof(V3F_T2F) * 6;
    vertices->resize(m_vertexEndOffset + expandSize);
    m_vertexEndOffset += expandSize;
    
    // Left top
    (*vertices)[0] = -halfWidth;
    (*vertices)[1] = halfHeight;
    (*vertices)[2] = 0.0f;
    (*vertices)[3] = leftUV;
    (*vertices)[4] = topUV;

    // Right top
    (*vertices)[5] = halfWidth;
    (*vertices)[6] = halfHeight;
    (*vertices)[7] = 0.0f;
    (*vertices)[8] = rightUV;
    (*vertices)[9] = topUV;
    
    // Right bottom
    (*vertices)[10] = halfWidth;
    (*vertices)[11] = -halfHeight;
    (*vertices)[12] = 0.0f;
    (*vertices)[13] = rightUV;
    (*vertices)[14] = bottomUV;
    
    // Right bottom
    (*vertices)[15] = halfWidth;
    (*vertices)[16] = -halfHeight;
    (*vertices)[17] = 0.0f;
    (*vertices)[18] = rightUV;
    (*vertices)[19] = bottomUV;

    // Left bottom
    (*vertices)[20] = -halfWidth;
    (*vertices)[21] = -halfHeight;
    (*vertices)[22] = 0.0f;
    (*vertices)[23] = leftUV;
    (*vertices)[24] = bottomUV;

    // Left top
    (*vertices)[25] = -halfWidth;
    (*vertices)[26] = halfHeight;
    (*vertices)[27] = 0.0f;
    (*vertices)[28] = leftUV;
    (*vertices)[29] = topUV;

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
