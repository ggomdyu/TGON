#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "CanvasSprite.h"

namespace tgon
{

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture) :
    m_texture(texture),
    m_textureRect(0, 0, static_cast<float>(m_texture->GetWidth()), static_cast<float>(m_texture->GetHeight())),
    m_enableScissorRect(false),
    m_blendMode(BlendMode::Normal)
{
}

CanvasSprite::CanvasSprite(CanvasSprite&& rhs) :
    m_texture(std::move(rhs.m_texture))
{
}

void CanvasSprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = {0, 0, static_cast<float>(m_texture->GetWidth()), static_cast<float>(m_texture->GetHeight())};
}

std::shared_ptr<Texture> CanvasSprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> CanvasSprite::GetTexture() const noexcept
{
    return m_texture;
}
    
void CanvasSprite::SetTextureRect(const FRect& textureRect)
{
    m_textureRect = textureRect;
}
    
FRect& CanvasSprite::GetTextureRect() noexcept
{
    return m_textureRect;
}
    
const FRect& CanvasSprite::GetTextureRect() const noexcept
{
    return m_textureRect;
}
    
void CanvasSprite::SetBlendMode(BlendMode blendMode) noexcept
{
    m_blendMode = blendMode;
}

BlendMode CanvasSprite::GetBlendMode() const noexcept
{
    return m_blendMode;
}
    
void CanvasSprite::EnableScissorRect() noexcept
{
    m_enableScissorRect = true;
}
    
void CanvasSprite::DisableScissorRect() noexcept
{
    m_enableScissorRect = false;
}
    
bool CanvasSprite::IsEnableScissorRect() const noexcept
{
    return m_enableScissorRect;
}

void CanvasSprite::SetScissorRect(const FRect& scissorRect) noexcept
{
    m_scissorRect = scissorRect;
}
    
FRect& CanvasSprite::GetScissorRect() noexcept
{
    return m_scissorRect;
}
    
const FRect& CanvasSprite::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

} /* namespace tgon */
