#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "UISprite.h"

namespace tgon
{

UISprite::UISprite(const std::shared_ptr<Texture>& texture, FilterMode filterMode, WrapMode wrapMode, BlendMode blendMode, Color4f blendColor) noexcept :
    m_texture(texture),
    m_textureRect(FRect(0, 0, static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height))),
    m_textureSize(texture->GetSize()),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_blendMode(blendMode),
    m_blendColor(blendColor)
{
}

UISprite::UISprite(UISprite&& rhs) noexcept :
    m_texture(std::move(rhs.m_texture)),
    m_textureRect(rhs.m_textureRect),
    m_textureSize(rhs.m_textureSize),
    m_filterMode(rhs.m_filterMode),
    m_wrapMode(rhs.m_wrapMode),
    m_blendMode(rhs.m_blendMode),
    m_blendColor(rhs.m_blendColor)
{
}

UISprite& UISprite::operator=(UISprite&& rhs) noexcept
{
    m_texture = std::move(rhs.m_texture);
    m_textureRect = rhs.m_textureRect;
    m_textureSize = rhs.m_textureSize;
    m_filterMode = rhs.m_filterMode;
    m_wrapMode = rhs.m_wrapMode;
    m_blendMode = rhs.m_blendMode;
    m_blendColor = rhs.m_blendColor;

    return *this;
}

void UISprite::SetTexture(std::shared_ptr<Texture>&& texture) noexcept
{
    m_textureSize = FExtent2D(static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height));
    m_textureRect = FRect(0, 0, m_textureSize.width, m_textureSize.height);
    m_texture = std::move(texture);
}

void UISprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_textureSize = FExtent2D(static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height));
    m_textureRect = FRect(0, 0, m_textureSize.width, m_textureSize.height);
    m_texture = texture;
}

void UISprite::SetTextureSize(const FExtent2D& textureSize) noexcept
{
    m_textureSize = textureSize;
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

void UISprite::SetPivot(const Vector2& pivot) noexcept
{
    m_pivot = pivot;
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

const Vector2& UISprite::GetPivot() const noexcept
{
    return m_pivot;
}

void UISprite::GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const
{
    UIBatch batch(m_material ? m_material : m_defaultMaterial, m_texture, m_filterMode, m_wrapMode, m_blendMode, static_cast<int32_t>(vertices->size()));
    if (batches->empty() || batches->back().CanBatch(batch) == false)
    {
        batches->push_back(batch);
    }

    batches->back().Merge(m_textureRect, m_textureSize, m_pivot, m_blendColor, matWorld, vertices);
}

} /* namespace tgon */
