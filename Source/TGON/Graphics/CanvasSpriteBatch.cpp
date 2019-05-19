#include "PrecompiledHeader.h"

#include "CanvasSpriteBatch.h"
#include "Texture.h"
#include "Graphics.h"
#include "Material.h"
#include "CanvasSprite.h"
#include "FVF.h"
#include "MeshUtility.h"
#include "Random/Random.h"

namespace tgon
{
    
CanvasSpriteBatch::CanvasSpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, const FRect& textureRect, int32_t vertexStartOffset) noexcept :
    m_texture(texture),
    m_blendMode(blendMode),
    m_enableScissorRect(enableScissorRect),
    m_scissorRect(scissorRect),
    m_vertexStartOffset(vertexStartOffset),
    m_vertexEndOffset(vertexStartOffset)
{
}

bool CanvasSpriteBatch::CanBatch(const CanvasSprite& rhs) const noexcept
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
    
void CanvasSpriteBatch::FlushBatch(Graphics& graphics)
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
    
    graphics.DrawPrimitives(PrimitiveType::Triangles, m_vertexStartOffset / (sizeof(V3F_T2F) / 4), (m_vertexEndOffset - m_vertexStartOffset) / (sizeof(V3F_T2F) / 4));
}
    
void CanvasSpriteBatch::Merge(const CanvasSprite& rhs, const Matrix4x4& matWorld, std::vector<float>* vertices)
{
    const auto& textureRect = rhs.GetTextureRect();
    const auto& textureSize = rhs.GetTexture()->GetSize();
    float leftUV = textureRect.x / textureSize.width;
    float topUV = textureRect.height / textureSize.height;
    float rightUV = textureRect.width / textureSize.width;
    float bottomUV = textureRect.y / textureSize.height;
    float halfWidth = textureRect.width * 0.5f;
    float halfHeight = textureRect.height * 0.5f;

    auto oldVertexEndOffset = m_vertexEndOffset;
    auto expandSize = sizeof(V3F_T2F) / 4 * 6;
    vertices->resize(m_vertexEndOffset + expandSize);
    m_vertexEndOffset += expandSize;

    // Left top
    V3F_T2F* newVertices = reinterpret_cast<V3F_T2F*>(&(*vertices)[oldVertexEndOffset]);
    newVertices[0].position = matWorld * Vector4(-halfWidth, halfHeight, 0.0f, 1.0f);
    newVertices[0].uv = {leftUV, topUV};
    
    // Right top
    newVertices[1].position = matWorld * Vector4(halfWidth, halfHeight, 0.0f, 1.0f);
    newVertices[1].uv = {rightUV, topUV};
    
    // Right bottom
    newVertices[2].position = matWorld * Vector4(halfWidth, -halfHeight, 0.0f, 1.0f);
    newVertices[2].uv = {rightUV, bottomUV};
    
    // Right bottom
    newVertices[3] = newVertices[2];

    // Left bottom
    newVertices[4].position = matWorld * Vector4(-halfWidth, -halfHeight, 0.0f, 1.0f);
    newVertices[4].uv = {leftUV, bottomUV};

    // Left top
    newVertices[5] = newVertices[0];
}

} /* namespace tgon */
