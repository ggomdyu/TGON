#include "PrecompiledHeader.h"

#include "Game/GameObject.h"

#include "UISpriteRendererComponent.h"

namespace tgon
{

UISpriteRendererComponent::UISpriteRendererComponent() :
    UIRendererComponent(nullptr, std::make_shared<UISprite>())
{
}

void UISpriteRendererComponent::SetTexture(std::shared_ptr<Texture>&& texture) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetTexture(std::move(texture));
}

void UISpriteRendererComponent::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetTexture(texture);
}

void UISpriteRendererComponent::SetTextureRect(const FRect& textureRect) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetTextureRect(textureRect);
}

void UISpriteRendererComponent::SetTextureSize(const FExtent2D& textureSize) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetTextureSize(textureSize);
}

void UISpriteRendererComponent::SetFilterMode(FilterMode filterMode) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetFilterMode(filterMode);
}

void UISpriteRendererComponent::SetWrapMode(WrapMode wrapMode) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetWrapMode(wrapMode);
}

void UISpriteRendererComponent::SetBlendMode(BlendMode blendMode) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetBlendMode(blendMode);
}

void UISpriteRendererComponent::SetBlendColor(const Color4f& blendColor) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetBlendColor(blendColor);
}

void UISpriteRendererComponent::SetPivot(const Vector2& pivot) noexcept
{
    std::static_pointer_cast<UISprite>(m_element)->SetPivot(pivot);
}

std::shared_ptr<Texture> UISpriteRendererComponent::GetTexture() noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetTexture();
}

std::shared_ptr<const Texture> UISpriteRendererComponent::GetTexture() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetTexture();
}

const FRect& UISpriteRendererComponent::GetTextureRect() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetTextureRect();
}

FilterMode UISpriteRendererComponent::GetFilterMode() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetFilterMode();
}

WrapMode UISpriteRendererComponent::GetWrapMode() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetWrapMode();
}

BlendMode UISpriteRendererComponent::GetBlendMode() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetBlendMode();
}

const Color4f& UISpriteRendererComponent::GetBlendColor() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetBlendColor();
}

const Vector2& UISpriteRendererComponent::GetPivot() const noexcept
{
    return std::static_pointer_cast<UISprite>(m_element)->GetPivot();
}

void UISpriteRendererComponent::Update()
{
    auto sprite = std::static_pointer_cast<UISprite>(m_element);
    if (sprite->GetTexture() == nullptr || sprite->GetBlendColor().a <= 0.0f)
    {
        return;
    }

    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_uiRendererModule->AddPrimitive(sprite, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
