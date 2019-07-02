#include "PrecompiledHeader.h"

#include "Graphics/Texture.h"

#include "CanvasSprite.h"
#include "Transform.h"

namespace tgon
{

CanvasSprite::CanvasSprite() noexcept :
    CanvasSprite(nullptr)
{
}

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture) noexcept :
    CanvasSprite(texture, nullptr)
{
}

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Transform>& transform) noexcept :
    CanvasSprite(texture, FRect(0, 0, static_cast<float>(texture->GetSize().width), static_cast<float>(texture->GetSize().height)), transform)
{
}

CanvasSprite::CanvasSprite(const std::shared_ptr<Texture>& texture, const FRect& textureRect, const std::shared_ptr<Transform>& transform) noexcept :
    m_texture(texture),
    m_transform(transform),
    m_textureRect(textureRect),
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
    rhs.m_textureRect = {};
    rhs.m_blendMode = {};
    rhs.m_scissorRect = {};
    rhs.m_enableScissorRect = false;
}

CanvasSprite& CanvasSprite::operator=(CanvasSprite&& rhs) noexcept
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

void CanvasSprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
    m_textureRect = FRect(0, 0, static_cast<float>(m_texture->GetSize().width), static_cast<float>(m_texture->GetSize().height));
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
