/**
 * @file    UIBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>

#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Math/Color.h"
#include "Math/Matrix4x4.h"

namespace tgon
{

class UIBatch
{
/**@section Constructor */
public:
    UIBatch(const std::shared_ptr<Texture>& texture, FilterMode filterMode, WrapMode wrapMode, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, int32_t vertexStartOffset) noexcept;
    
/**@section Method */
public:
    bool CanBatch(const UIBatch& rhs) const noexcept;
    void Merge(float x, float y, const FRect& textureRect, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices);
    void Merge(const FRect& textureRect, const FExtent2D& textureSize, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices);
    void FlushBatch(Graphics& graphics);
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    FilterMode GetFilterMode() const noexcept;
    BlendMode GetBlendMode() const noexcept;
    bool IsEnableScissorRect() const noexcept;
    const FRect& GetScissorRect() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    FilterMode m_filterMode;
    WrapMode m_wrapMode;
    BlendMode m_blendMode;
    bool m_enableScissorRect;
    FRect m_scissorRect;
    int32_t m_vertexStartOffset;
    int32_t m_vertexEndOffset;
};

} /* namespace tgon */
