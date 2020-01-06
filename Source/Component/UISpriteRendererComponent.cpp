#include "PrecompiledHeader.h"

#include "Game/GameObject.h"

#include "UISpriteRendererComponent.h"

namespace tgon
{

UISpriteRendererComponent::UISpriteRendererComponent() :
    UIRendererComponent(),
    m_sprite(std::make_shared<UISprite>())
{
}

void UISpriteRendererComponent::SetTexture(std::shared_ptr<Texture>&& texture) noexcept
{
    m_sprite->SetTexture(std::move(texture));
}

void UISpriteRendererComponent::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_sprite->SetTexture(texture);
}

void UISpriteRendererComponent::SetTextureRect(const FRect& textureRect) noexcept
{
    m_sprite->SetTextureRect(textureRect);
}

void UISpriteRendererComponent::SetTextureSize(const FExtent2D& textureSize) noexcept
{
    m_sprite->SetTextureSize(textureSize);
}

void UISpriteRendererComponent::SetFilterMode(FilterMode filterMode) noexcept
{
    m_sprite->SetFilterMode(filterMode);
}

void UISpriteRendererComponent::SetWrapMode(WrapMode wrapMode) noexcept
{
    m_sprite->SetWrapMode(wrapMode);
}

void UISpriteRendererComponent::SetBlendMode(BlendMode blendMode) noexcept
{
    m_sprite->SetBlendMode(blendMode);
}

void UISpriteRendererComponent::SetBlendColor(const Color4f& blendColor) noexcept
{
    m_sprite->SetBlendColor(blendColor);
}

void UISpriteRendererComponent::SetScissorRect(const FRect& rect) noexcept
{
    m_sprite->SetScissorRect(rect);
}

void UISpriteRendererComponent::SetPivot(const Vector2& pivot) noexcept
{
    m_sprite->SetPivot(pivot);
}

void UISpriteRendererComponent::EnableScissorRect() noexcept
{
    m_sprite->EnableScissorRect();
}

void UISpriteRendererComponent::DisableScissorRect() noexcept
{
    m_sprite->DisableScissorRect();
}

std::shared_ptr<Texture> UISpriteRendererComponent::GetTexture() noexcept
{
    return m_sprite->GetTexture();
}

std::shared_ptr<const Texture> UISpriteRendererComponent::GetTexture() const noexcept
{
    return m_sprite->GetTexture();
}

const FRect& UISpriteRendererComponent::GetTextureRect() const noexcept
{
    return m_sprite->GetTextureRect();
}

FilterMode UISpriteRendererComponent::GetFilterMode() const noexcept
{
    return m_sprite->GetFilterMode();
}

WrapMode UISpriteRendererComponent::GetWrapMode() const noexcept
{
    return m_sprite->GetWrapMode();
}

BlendMode UISpriteRendererComponent::GetBlendMode() const noexcept
{
    return m_sprite->GetBlendMode();
}

const Color4f& UISpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_sprite->GetBlendColor();
}

bool UISpriteRendererComponent::IsEnableScissorRect() const noexcept
{
    return m_sprite->IsEnableScissorRect();
}

const FRect& UISpriteRendererComponent::GetScissorRect() const noexcept
{
    return m_sprite->GetScissorRect();
}
 
const Vector2& UISpriteRendererComponent::GetPivot() const noexcept
{
    return m_sprite->GetPivot();
}

void UISpriteRendererComponent::Update()
{
    if (m_sprite->GetTexture() == nullptr || m_sprite->GetBlendColor().a <= 0.0f)
    {
        return;
    }

    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_uiRendererModule->AddUIElement(m_sprite, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
