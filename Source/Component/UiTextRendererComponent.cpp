#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Game/GameObject.h"
#include "Engine/AssetModule.h"

#include "UITextRendererComponent.h"

namespace tgon
{

UITextRendererComponent::UITextRendererComponent() :
    UIRendererComponent(),
    m_text(std::make_shared<UIText>())
{
}

void UITextRendererComponent::SetFontAtlas(const char* fontAtlasPath)
{
    auto fontAtlas = Application::GetEngine()->FindModule<AssetModule>()->GetResource<FontAtlas>(fontAtlasPath);
    m_text->SetFontAtlas(std::move(fontAtlas));
}

void UITextRendererComponent::SetFontAtlas(const std::shared_ptr<FontAtlas>& fontAtlas) noexcept
{
    m_text->SetFontAtlas(fontAtlas);
}

void UITextRendererComponent::SetFontAtlas(std::shared_ptr<FontAtlas>&& fontAtlas) noexcept
{
    m_text->SetFontAtlas(std::move(fontAtlas));
}

void UITextRendererComponent::SetText(const std::string_view& text)
{
    m_text->SetText(text);
}

void UITextRendererComponent::SetFontSize(int32_t fontSize) noexcept
{
    m_text->SetFontSize(fontSize);
}

void UITextRendererComponent::SetLineSpacing(float lineSpacing) noexcept
{
    m_text->SetLineSpacing(lineSpacing);
}

void UITextRendererComponent::SetLineBreakMode(LineBreakMode lineBreakMode) noexcept
{
    m_text->SetLineBreakMode(lineBreakMode);
}

void UITextRendererComponent::SetTextAlignment(TextAlignment textAlignment) noexcept
{
    m_text->SetTextAlignment(textAlignment);
}

void UITextRendererComponent::SetBlendColor(const Color4f& color) noexcept
{
    m_text->SetBlendColor(color);
}

void UITextRendererComponent::SetRect(const I32Rect& rect) noexcept
{
    m_text->SetRect(rect);
}

void UITextRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

LineBreakMode UITextRendererComponent::GetLineBreakMode() const noexcept
{
    return m_text->GetLineBreakMode();
}

TextAlignment UITextRendererComponent::GetTextAlignment() const noexcept
{
    return m_text->GetTextAlignment();
}

const Color4f& UITextRendererComponent::GetBlendColor() const noexcept
{
    return m_text->GetBlendColor();
}

std::shared_ptr<const FontAtlas> UITextRendererComponent::GetFontAtlas() const noexcept
{
    return m_text->GetFontAtlas();
}

std::shared_ptr<FontAtlas> UITextRendererComponent::GetFontAtlas() noexcept
{
    return m_text->GetFontAtlas();
}

int32_t UITextRendererComponent::GetFontSize() const noexcept
{
    return m_text->GetFontSize();
}

const I32Rect& UITextRendererComponent::GetRect() const noexcept
{
    return m_text->GetRect();
}

int32_t UITextRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

void UITextRendererComponent::Update()
{
    if (m_text->GetBlendColor().a <= 0.0f)
    {
        return;
    }
    
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_uiRendererModule->AddUIElement(m_text, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
