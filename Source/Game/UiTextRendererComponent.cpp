#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Game/GameObject.h"
#include "Engine/AssetModule.h"

#include "UITextRendererComponent.h"

namespace tg
{

UITextRendererComponent::UITextRendererComponent() :
    UIRendererComponent(nullptr, std::make_shared<UIText>())
{
}

void UITextRendererComponent::SetFontAtlas(const char* fontAtlasPath)
{
    auto fontAtlas = Application::GetEngine()->FindModule<AssetModule>()->GetResource<FontAtlas>(fontAtlasPath);
    std::static_pointer_cast<UIText>(m_element)->SetFontAtlas(std::move(fontAtlas));
}

void UITextRendererComponent::SetFontAtlas(const std::shared_ptr<FontAtlas>& fontAtlas) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetFontAtlas(fontAtlas);
}

void UITextRendererComponent::SetFontAtlas(std::shared_ptr<FontAtlas>&& fontAtlas) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetFontAtlas(std::move(fontAtlas));
}

void UITextRendererComponent::SetText(const std::string_view& text)
{
    std::static_pointer_cast<UIText>(m_element)->SetText(text);
}

void UITextRendererComponent::SetFontSize(int32_t fontSize) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetFontSize(fontSize);
}

void UITextRendererComponent::SetLineSpacing(float lineSpacing) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetLineSpacing(lineSpacing);
}

void UITextRendererComponent::SetLineBreakMode(LineBreakMode lineBreakMode) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetLineBreakMode(lineBreakMode);
}

void UITextRendererComponent::SetTextAlignment(TextAlignment textAlignment) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetTextAlignment(textAlignment);
}

void UITextRendererComponent::SetBlendColor(const Color4f& color) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetBlendColor(color);
}

void UITextRendererComponent::SetRect(const I32Rect& rect) noexcept
{
    std::static_pointer_cast<UIText>(m_element)->SetRect(rect);
}

void UITextRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

LineBreakMode UITextRendererComponent::GetLineBreakMode() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetLineBreakMode();
}

TextAlignment UITextRendererComponent::GetTextAlignment() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetTextAlignment();
}

const Color4f& UITextRendererComponent::GetBlendColor() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetBlendColor();
}

std::shared_ptr<const FontAtlas> UITextRendererComponent::GetFontAtlas() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetFontAtlas();
}

std::shared_ptr<FontAtlas> UITextRendererComponent::GetFontAtlas() noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetFontAtlas();
}

int32_t UITextRendererComponent::GetFontSize() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetFontSize();
}

const I32Rect& UITextRendererComponent::GetRect() const noexcept
{
    return std::static_pointer_cast<UIText>(m_element)->GetRect();
}

int32_t UITextRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

void UITextRendererComponent::Update()
{
    auto text = std::static_pointer_cast<UIText>(m_element);
    if (text->GetBlendColor().a <= 0.0f)
    {
        return;
    }
    
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_uiRendererModule->AddPrimitive(text, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

}
