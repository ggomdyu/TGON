#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"
#include "Graphics/Transform.h"

#include "UISprite.h"

namespace tgon
{

UISprite::UISprite() noexcept :
    UISprite(nullptr)
{
}

UISprite::UISprite(const std::shared_ptr<Texture>& texture) noexcept :
    UISprite(texture, FRect(0, 0, static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height)))
{
}

UISprite::UISprite(const std::shared_ptr<Texture>& texture, const FRect& textureRect) noexcept :
    m_texture(texture),
    m_textureRect(textureRect),
    m_blendMode(BlendMode::Normal),
    m_blendColor(1.0f, 1.0f, 1.0f, 1.0f),
    m_enableScissorRect(false)
{
}

UISprite::UISprite(UISprite&& rhs) noexcept :
    m_texture(std::move(rhs.m_texture)),
    m_textureRect(rhs.m_textureRect),
    m_blendMode(rhs.m_blendMode),
    m_blendColor(rhs.m_blendColor),
    m_scissorRect(rhs.m_scissorRect),
    m_enableScissorRect(rhs.m_enableScissorRect)
{
    rhs.m_textureRect = {};
    rhs.m_blendMode = {};
    rhs.m_blendColor = {};
    rhs.m_scissorRect = {};
    rhs.m_enableScissorRect = false;
}

UISprite& UISprite::operator=(UISprite&& rhs) noexcept
{
    m_texture = std::move(rhs.m_texture);
    m_blendMode = rhs.m_blendMode;
    m_textureRect = rhs.m_textureRect;
    m_scissorRect = rhs.m_scissorRect;
    m_enableScissorRect = rhs.m_enableScissorRect;

    rhs.m_textureRect = {};
    rhs.m_blendMode = {};
    rhs.m_scissorRect = {};
    rhs.m_enableScissorRect = false;

    return *this;
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
    
FRect& UISprite::GetScissorRect() noexcept
{
    return m_scissorRect;
}
    
const FRect& UISprite::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

} /* namespace tgon */
