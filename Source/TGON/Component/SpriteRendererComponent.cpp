#include "PrecompiledHeader.h"

#include "Engine/GraphicsModule.h"
#include "Game/GameObject.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent() :
    RendererComponent(),
    m_sprite(std::make_shared<UISprite>())
{
}

void SpriteRendererComponent::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_sprite->SetTexture(texture);
}

void SpriteRendererComponent::SetTextureRect(const FRect& textureRect) noexcept
{
    m_sprite->SetTextureRect(textureRect);
}

void SpriteRendererComponent::SetTextureSize(const FExtent2D& textureSize) noexcept
{
    m_sprite->SetTextureSize(textureSize);
}

void SpriteRendererComponent::SetFilterMode(FilterMode filterMode) noexcept
{
    m_sprite->SetFilterMode(filterMode);
}

void SpriteRendererComponent::SetWrapMode(WrapMode wrapMode) noexcept
{
    m_sprite->SetWrapMode(wrapMode);
}

void SpriteRendererComponent::SetBlendMode(BlendMode blendMode) noexcept
{
    m_sprite->SetBlendMode(blendMode);
}

void SpriteRendererComponent::SetBlendColor(const Color4f& blendColor) noexcept
{
    m_sprite->SetBlendColor(blendColor);
}

void SpriteRendererComponent::SetScissorRect(const FRect& rect) noexcept
{
    m_sprite->SetScissorRect(rect);
}

void SpriteRendererComponent::SetPivot(const Vector2& pivot) noexcept
{
    m_sprite->SetPivot(pivot);
}

void SpriteRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

void SpriteRendererComponent::EnableScissorRect() noexcept
{
    m_sprite->EnableScissorRect();
}

void SpriteRendererComponent::DisableScissorRect() noexcept
{
    m_sprite->DisableScissorRect();
}

std::shared_ptr<Texture> SpriteRendererComponent::GetTexture() noexcept
{
    return m_sprite->GetTexture();
}

std::shared_ptr<const Texture> SpriteRendererComponent::GetTexture() const noexcept
{
    return m_sprite->GetTexture();
}

const FRect& SpriteRendererComponent::GetTextureRect() const noexcept
{
    return m_sprite->GetTextureRect();
}

FilterMode SpriteRendererComponent::GetFilterMode() const noexcept
{
    return m_sprite->GetFilterMode();
}

WrapMode SpriteRendererComponent::GetWrapMode() const noexcept
{
    return m_sprite->GetWrapMode();
}

BlendMode SpriteRendererComponent::GetBlendMode() const noexcept
{
    return m_sprite->GetBlendMode();
}

const Color4f& SpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_sprite->GetBlendColor();
}

bool SpriteRendererComponent::IsEnableScissorRect() const noexcept
{
    return m_sprite->IsEnableScissorRect();
}

const FRect& SpriteRendererComponent::GetScissorRect() const noexcept
{
    return m_sprite->GetScissorRect();
}
 
const Vector2& SpriteRendererComponent::GetPivot() const noexcept
{
    return m_sprite->GetPivot();
}

int32_t SpriteRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

void SpriteRendererComponent::Update()
{
    if (m_sprite->GetTexture() == nullptr || m_sprite->GetBlendColor().a <= 0.0f)
    {
        return;
    }

    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_graphicsModule->GetUIRenderer().AddUIElement(m_sprite, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
