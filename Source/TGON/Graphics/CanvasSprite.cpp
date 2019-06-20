#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "CanvasSprite.h"
#include "Transform.h"

namespace tgon
{

CanvasSprite::CanvasSprite() noexcept :
    CanvasSprite(nullptr, nullptr)
{
}

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture) noexcept :
    CanvasSprite(texture, nullptr)
{
}

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Transform>& transform) noexcept :
    m_texture(texture),
    m_transform(transform),
    m_textureRect(0, 0, static_cast<float>(m_texture->GetSize().width), static_cast<float>(m_texture->GetSize().height)),
    m_enableScissorRect(false),
    m_blendMode(BlendMode::Normal)
{
}

CanvasSprite::CanvasSprite(CanvasSprite&& rhs) noexcept :
    m_texture(std::move(rhs.m_texture)),
    m_transform(std::move(rhs.m_transform)),
    m_blendMode(rhs.m_blendMode),
    m_textureRect(rhs.m_textureRect),
    m_scissorRect(rhs.m_scissorRect),
    m_enableScissorRect(rhs.m_enableScissorRect)
{
}

CanvasSprite& CanvasSprite::operator=(const CanvasSprite& rhs) noexcept
{
    if (this == &rhs)
    {
        m_texture = std::move(rhs.m_texture);
        m_transform = std::move(rhs.m_transform);
        m_blendMode = rhs.m_blendMode;
        m_textureRect = rhs.m_textureRect;
        m_scissorRect = rhs.m_scissorRect;
        m_enableScissorRect = rhs.m_enableScissorRect;
    }

    return *this;
}

void CanvasSprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = {0, 0, static_cast<float>(m_texture->GetSize().width), static_cast<float>(m_texture->GetSize().height)};
}

std::shared_ptr<Texture> CanvasSprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> CanvasSprite::GetTexture() const noexcept
{
    return m_texture;
}

std::shared_ptr<Transform> CanvasSprite::GetTransform() noexcept
{
    return m_transform;
}

std::shared_ptr<const Transform> CanvasSprite::GetTransform() const noexcept
{
    return m_transform;
}
    
void CanvasSprite::SetTextureRect(const FRect& textureRect)
{
    m_textureRect = textureRect;
}

void CanvasSprite::SetTransform(const std::shared_ptr<Transform>& transform) noexcept
{
    m_transform = transform;
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
