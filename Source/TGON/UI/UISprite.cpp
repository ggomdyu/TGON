#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "UISprite.h"

namespace tgon
{

UISprite::UISprite(const std::shared_ptr<Texture>& texture, FilterMode filterMode, WrapMode wrapMode, BlendMode blendMode, Color4f blendColor) noexcept :
    m_texture(texture),
    m_textureRect(FRect(0, 0, static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height))),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_blendMode(blendMode),
    m_blendColor(blendColor)
{
}

void UISprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = FRect(0, 0, static_cast<float>(m_texture->GetSize().width), static_cast<float>(m_texture->GetSize().height));
}

void UISprite::SetTextureRect(const FRect& textureRect) noexcept
{
    m_textureRect = textureRect;
}

void UISprite::SetFilterMode(FilterMode filterMode) noexcept
{
    m_filterMode = filterMode;
}

void UISprite::SetWrapMode(WrapMode wrapMode) noexcept
{
    m_wrapMode = wrapMode;
}

void UISprite::SetBlendMode(BlendMode blendMode) noexcept
{
    m_blendMode = blendMode;
}

void UISprite::SetBlendColor(const Color4f& blendColor) noexcept
{
    m_blendColor = blendColor;
}

void UISprite::SetScissorRect(const FRect& scissorRect) noexcept
{
    m_scissorRect = scissorRect;
}

void UISprite::SetPivot(const Vector2& pivot) noexcept
{
    m_pivot = pivot;
}

void UISprite::EnableScissorRect() noexcept
{
    m_enableScissorRect = true;
}

void UISprite::DisableScissorRect() noexcept
{
    m_enableScissorRect = false;
}

std::shared_ptr<Texture> UISprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> UISprite::GetTexture() const noexcept
{
    return m_texture;
}

const FRect& UISprite::GetTextureRect() const noexcept
{
    return m_textureRect;
}

FilterMode UISprite::GetFilterMode() const noexcept
{
    return m_filterMode;
}

WrapMode UISprite::GetWrapMode() const noexcept
{
    return m_wrapMode;
}

BlendMode UISprite::GetBlendMode() const noexcept
{
    return m_blendMode;
}

const Color4f& UISprite::GetBlendColor() const noexcept
{
    return m_blendColor;
}

bool UISprite::IsEnableScissorRect() const noexcept
{
    return m_enableScissorRect;
}

const FRect& UISprite::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

const Vector2& UISprite::GetPivot() const noexcept
{
    return m_pivot;
}

void UISprite::GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const
{
    UIBatch batch(m_texture, m_filterMode, m_wrapMode, m_blendMode, m_enableScissorRect, m_scissorRect, static_cast<int32_t>(vertices->size()));
    if (batches->empty() || batches->back().CanBatch(batch) == false)
    {
        batches->push_back(batch);
    }

    batches->back().Merge(m_textureRect, m_pivot, m_blendColor, matWorld, vertices);
}

} /* namespace tgon */
