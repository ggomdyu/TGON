#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "Sprite.h"
#include "Transform.h"

namespace tgon
{

Sprite::Sprite() noexcept :
    Sprite(nullptr)
{
}

Sprite::Sprite(const std::shared_ptr<Texture>& texture) noexcept :
    Sprite(texture, nullptr)
{
}

Sprite::Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Transform>& transform) noexcept :
    Sprite(texture, FRect(0, 0, static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height)), transform)
{
}

Sprite::Sprite(const std::shared_ptr<Texture>& texture, const FRect& textureRect, const std::shared_ptr<Transform>& transform) noexcept :
    m_texture(texture),
    m_transform(transform),
    m_textureRect(textureRect),
    m_enableScissorRect(false),
    m_blendMode(BlendMode::Normal)
{
}

Sprite::Sprite(Sprite&& rhs) noexcept :
    m_texture(std::move(rhs.m_texture)),
    m_transform(std::move(rhs.m_transform)),
    m_blendMode(rhs.m_blendMode),
    m_textureRect(rhs.m_textureRect),
    m_scissorRect(rhs.m_scissorRect),
    m_enableScissorRect(rhs.m_enableScissorRect)
{
    rhs.m_textureRect = {};
    rhs.m_blendMode = {};
    rhs.m_scissorRect = {};
    rhs.m_enableScissorRect = false;
}

Sprite& Sprite::operator=(Sprite&& rhs) noexcept
{
    if (this == &rhs)
    {
        m_texture = std::move(rhs.m_texture);
        m_transform = std::move(rhs.m_transform);
        m_blendMode = rhs.m_blendMode;
        m_textureRect = rhs.m_textureRect;
        m_scissorRect = rhs.m_scissorRect;
        m_enableScissorRect = rhs.m_enableScissorRect;

        rhs.m_textureRect = {};
        rhs.m_blendMode = {};
        rhs.m_scissorRect = {};
        rhs.m_enableScissorRect = false;
    }

    return *this;
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = FRect(0, 0, static_cast<float>(m_texture->GetSize().width), static_cast<float>(m_texture->GetSize().height));
}

std::shared_ptr<Texture> Sprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> Sprite::GetTexture() const noexcept
{
    return m_texture;
}

std::shared_ptr<Transform> Sprite::GetTransform() noexcept
{
    return m_transform;
}

std::shared_ptr<const Transform> Sprite::GetTransform() const noexcept
{
    return m_transform;
}
    
void Sprite::SetTextureRect(const FRect& textureRect)
{
    m_textureRect = textureRect;
}

void Sprite::SetTransform(const std::shared_ptr<Transform>& transform) noexcept
{
    m_transform = transform;
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

} /* namespace tgon */
