#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "Sprite.h"

namespace tgon
{

Sprite::Sprite(const std::shared_ptr<Texture>& texture) :
    m_texture(texture),
    m_textureRect(0, 0, static_cast<float>(m_texture->GetWidth()), static_cast<float>(m_texture->GetHeight())),
    m_enableScissorRect(false),
    m_layer(0),
    m_blendMode(BlendMode::Normal)
{
}

Sprite::Sprite(Sprite&& rhs) :
    m_texture(std::move(rhs.m_texture))
{
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = {0, 0, static_cast<float>(m_texture->GetWidth()), static_cast<float>(m_texture->GetHeight())};
}

std::shared_ptr<Texture> Sprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> Sprite::GetTexture() const noexcept
{
    return m_texture;
}
    
void Sprite::SetTextureRect(const FRect& textureRect)
{
    m_textureRect = textureRect;
}
    
FRect& Sprite::GetTextureRect() noexcept
{
    return m_textureRect;
}
    
const FRect& Sprite::GetTextureRect() const noexcept
{
    return m_textureRect;
}
    
void Sprite::SetBlendMode(BlendMode blendMode) noexcept
{
    m_blendMode = blendMode;
}

BlendMode Sprite::GetBlendMode() const noexcept
{
    return m_blendMode;
}
    
void Sprite::EnableScissorRect() noexcept
{
    m_enableScissorRect = true;
}
    
void Sprite::DisableScissorRect() noexcept
{
    m_enableScissorRect = false;
}
    
bool Sprite::IsEnableScissorRect() const noexcept
{
    return m_enableScissorRect;
}

void Sprite::SetScissorRect(const FRect& scissorRect) noexcept
{
    m_scissorRect = scissorRect;
}
    
FRect& Sprite::GetScissorRect() noexcept
{
    return m_scissorRect;
}
    
const FRect& Sprite::GetScissorRect() const noexcept
{
    return m_scissorRect;
}
    
void Sprite::SetLayer(int32_t layer) noexcept
{
    m_layer = layer;
}

int32_t Sprite::GetLayer() const noexcept
{
    return m_layer;
}

} /* namespace tgon */
