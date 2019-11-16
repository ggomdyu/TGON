/**
 * @file    UISpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>

#include "Math/Matrix4x4.h"

#include "UISprite.h"

namespace tgon
{

class TGON_API UISpriteBatch final
{
/**@section Constructor */
public:
    UISpriteBatch(const std::shared_ptr<Texture>& texture, FilterMode filterMode, WrapMode wrapMode, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, int32_t vertexStartOffset) noexcept;
    
/**@section Method */
public:
    bool CanBatch(const UISprite& rhs) const noexcept;
    void Merge(const UISprite& rhs, const Matrix4x4& matWorld, std::vector<float>* vertices);
    void FlushBatch(Graphics& graphics);
    
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
