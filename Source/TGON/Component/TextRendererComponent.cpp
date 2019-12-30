#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Engine/AssetModule.h"
#include "Game/GameObject.h"

#include "TextRendererComponent.h"

namespace tgon
{

TextRendererComponent::TextRendererComponent() :
    RendererComponent(),
    m_text(std::make_shared<UIText>())
{
}

void TextRendererComponent::SetFontAtlas(const char* fontAtlasPath)
{
    auto assetModule = Application::GetEngine()->FindModule<AssetModule>();
    this->SetFontAtlas(assetModule->GetResource<FontAtlas>(fontAtlasPath));
}

void TextRendererComponent::SetFontAtlas(const std::shared_ptr<FontAtlas>& fontAtlas) noexcept
{
    m_text->SetFontAtlas(fontAtlas);
}

void TextRendererComponent::SetText(const std::string_view& text)
{
    m_text->SetText(text);
}

void TextRendererComponent::SetFontSize(int32_t fontSize) noexcept
{
    m_text->SetFontSize(fontSize);
}

void TextRendererComponent::SetLineSpacing(float lineSpacing) noexcept
{
    m_text->SetLineSpacing(lineSpacing);
}

void TextRendererComponent::SetLineBreakMode(LineBreakMode lineBreakMode) noexcept
{
    m_text->SetLineBreakMode(lineBreakMode);
}

void TextRendererComponent::SetTextAlignment(TextAlignment textAlignment) noexcept
{
    m_text->SetTextAlignment(textAlignment);
}

void TextRendererComponent::SetBlendColor(const Color4f& color) noexcept
{
    m_text->SetBlendColor(color);
}

void TextRendererComponent::SetRect(const I32Rect& rect) noexcept
{
    m_text->SetRect(rect);
}

void TextRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

LineBreakMode TextRendererComponent::GetLineBreakMode() const noexcept
{
    return m_text->GetLineBreakMode();
}

TextAlignment TextRendererComponent::GetTextAlignment() const noexcept
{
    return m_text->GetTextAlignment();
}

const Color4f& TextRendererComponent::GetBlendColor() const noexcept
{
    return m_text->GetBlendColor();
}

std::shared_ptr<const FontAtlas> TextRendererComponent::GetFontAtlas() const noexcept
{
    return m_text->GetFontAtlas();
}

std::shared_ptr<FontAtlas> TextRendererComponent::GetFontAtlas() noexcept
{
    return m_text->GetFontAtlas();
}

int32_t TextRendererComponent::GetFontSize() const noexcept
{
    return m_text->GetFontSize();
}

const I32Rect& TextRendererComponent::GetRect() const noexcept
{
    return m_text->GetRect();
}

int32_t TextRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

void TextRendererComponent::Update()
{
    if (m_text->GetBlendColor().a <= 0.0f)
    {
        return;
    }
    
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_graphicsModule->GetUIRenderer().AddUIElement(m_text, m_sortingLayer, gameObject->FindComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
