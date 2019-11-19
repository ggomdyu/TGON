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

std::shared_ptr<Texture> UISprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> UISprite::GetTexture() const noexcept
{
    return m_texture;
}

void UISprite::SetTextureRect(const FRect& textureRect) noexcept
{
    m_textureRect = textureRect;
}

FRect& UISprite::GetTextureRect() noexcept
{
    return m_textureRect;
}
    
const FRect& UISprite::GetTextureRect() const noexcept
{
    return m_textureRect;
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
    
void UISprite::EnableScissorRect() noexcept
{
    m_enableScissorRect = true;
}
    
void UISprite::DisableScissorRect() noexcept
{
    m_enableScissorRect = false;
}
    
bool UISprite::IsEnableScissorRect() const noexcept
{
    return m_enableScissorRect;
}

void UISprite::SetScissorRect(const FRect& scissorRect) noexcept
{
    m_scissorRect = scissorRect;
}

const FRect& UISprite::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

const Vector2& UISprite::GetPivot() const noexcept
{
    return m_pivot;
}

} /* namespace tgon */
