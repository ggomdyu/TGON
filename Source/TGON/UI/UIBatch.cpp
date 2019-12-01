#include "PrecompiledHeader.h"

#include "Math/Vector4.h"
#include "Graphics/Texture.h"
#include "Graphics/Graphics.h"
#include "Graphics/Material.h"
#include "Graphics/VertexFormat.h"

#include "UIBatch.h"

namespace tgon
{
    
UIBatch::UIBatch(const std::shared_ptr<Texture>& texture, FilterMode filterMode, WrapMode wrapMode, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, int32_t vertexStartOffset) noexcept :
    m_texture(texture),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_blendMode(blendMode),
    m_enableScissorRect(enableScissorRect),
    m_scissorRect(scissorRect),
    m_vertexStartOffset(vertexStartOffset),
    m_vertexEndOffset(vertexStartOffset)
{
}

bool UIBatch::CanBatch(const UIBatch& rhs) const noexcept
{
    if (m_texture == rhs.m_texture &&
        m_filterMode == rhs.m_filterMode &&
        m_wrapMode == rhs.m_wrapMode &&
        m_blendMode == rhs.m_blendMode &&
        m_enableScissorRect == rhs.m_enableScissorRect &&
        m_scissorRect == rhs.m_scissorRect)
    {
        return true;
    }
    
    return false;
}
    
void UIBatch::FlushBatch(Graphics& graphics)
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
    
    graphics.DrawPrimitives(PrimitiveType::Triangles, m_vertexStartOffset / (sizeof(V3F_C4F_T2F) / 4), (m_vertexEndOffset - m_vertexStartOffset) / (sizeof(V3F_C4F_T2F) / 4));
}

void UIBatch::Merge(float x, float y, const FRect& textureRect, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices)
{
    decltype(auto) textureSize = m_texture->GetSize();
        
    float leftUV = textureRect.x / textureSize.width;
    float rightUV = (textureRect.x + textureRect.width) / textureSize.width;
#if TGON_GRAPHICS_OPENGL
    float topUV = textureRect.y / textureSize.height;
    float bottomUV = (textureRect.y + textureRect.height) / textureSize.height;
#else
    float topUV = (textureRect.y + textureRect.height) / textureSize.height;
    float bottomUV = textureRect.y / textureSize.height;
#endif
    float halfWidth = 0.5f * textureRect.width;
    float halfHeight = 0.5f * textureRect.height;
    float xOffset = x + (pivot.x - 0.5f) * -textureRect.width;
    float yOffset = y + (pivot.y - 0.5f) * textureRect.height;

    int32_t oldVertexEndOffset = m_vertexEndOffset;
    int32_t expandSize = sizeof(V3F_C4F_T2F) / 4 * 6;
    vertices->resize(static_cast<size_t>(m_vertexEndOffset) + expandSize);
    m_vertexEndOffset += expandSize;

    // Left top
    V3F_C4F_T2F* newVertices = reinterpret_cast<V3F_C4F_T2F*>(&(*vertices)[oldVertexEndOffset]);
    newVertices[0].position = Vector4(-halfWidth + xOffset, halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[0].color = blendColor;
    newVertices[0].uv = {leftUV, topUV};

    // Right top
    newVertices[1].position = Vector4(halfWidth + xOffset, halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[1].color = blendColor;
    newVertices[1].uv = {rightUV, topUV};

    // Right bottom
    newVertices[2].position = Vector4(halfWidth + xOffset, -halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[2].color = blendColor;
    newVertices[2].uv = {rightUV, bottomUV};

    // Right bottom
    newVertices[3] = newVertices[2];

    // Left bottom
    newVertices[4].position = Vector4(-halfWidth + xOffset, -halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[4].color = blendColor;
    newVertices[4].uv = {leftUV, bottomUV};

    // Left top
    newVertices[5] = newVertices[0];
}
    
void UIBatch::Merge(const FRect& textureRect, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices)
{
    decltype(auto) textureSize = m_texture->GetSize();
    
    float leftUV = textureRect.x / textureSize.width;
    float rightUV = (textureRect.x + textureRect.width) / textureSize.width;
#if TGON_GRAPHICS_OPENGL
    float topUV = textureRect.y / textureSize.height;
    float bottomUV = (textureRect.y + textureRect.height) / textureSize.height;
#else
    float topUV = (textureRect.y + textureRect.height) / textureSize.height;
    float bottomUV = textureRect.y / textureSize.height;
#endif
    float halfWidth = textureRect.width * 0.5f;
    float halfHeight = textureRect.height * 0.5f;
    float xOffset = -textureRect.width * (pivot.x - 0.5f);
    float yOffset = textureRect.height * (pivot.y - 0.5f);

    int32_t oldVertexEndOffset = m_vertexEndOffset;
    int32_t expandSize = sizeof(V3F_C4F_T2F) / 4 * 6;
    vertices->resize(static_cast<size_t>(m_vertexEndOffset) + expandSize);
    m_vertexEndOffset += expandSize;

    // Left top
    V3F_C4F_T2F* newVertices = reinterpret_cast<V3F_C4F_T2F*>(&(*vertices)[oldVertexEndOffset]);
    newVertices[0].position = Vector4(-halfWidth + xOffset, halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[0].color = blendColor;
    newVertices[0].uv = {leftUV, topUV};
    
    // Right top
    newVertices[1].position = Vector4(halfWidth + xOffset, halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[1].color = blendColor;
    newVertices[1].uv = {rightUV, topUV};
    
    // Right bottom
    newVertices[2].position = Vector4(halfWidth + xOffset, -halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[2].color = blendColor;
    newVertices[2].uv = {rightUV, bottomUV};
    
    // Right bottom
    newVertices[3] = newVertices[2];

    // Left bottom
    newVertices[4].position = Vector4(-halfWidth + xOffset, -halfHeight + yOffset, 0.0f, 1.0f) * matWorld;
    newVertices[4].color = blendColor;
    newVertices[4].uv = {leftUV, bottomUV};

    // Left top
    newVertices[5] = newVertices[0];
}

} /* namespace tgon */
