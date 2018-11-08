#include "PrecompiledHeader.h"

#include "Graphics/LowLevel/Texture.h"

#include "Sprite.h"

namespace tgon
{

Sprite::Sprite(const std::shared_ptr<Texture>& texture) :
    m_texture(texture)
{
}

Sprite::Sprite(Sprite&& rhs) :
    m_texture(std::move(rhs.m_texture))
{
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
}

std::shared_ptr<Texture>& Sprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> Sprite::GetTexture() const noexcept
{
    return m_texture;
}

} /* namespace tgon */
