#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Engine/AssetModule.h"

#include "UIText.h"

namespace tgon
{

void UIText::SetFont(const char* fontPath, int32_t fontSize)
{
    auto assetModule = Application::GetEngine()->FindModule<AssetModule>();
    this->SetFont(assetModule->GetFont(fontPath), fontSize);
}

void UIText::SetFont(const std::shared_ptr<Font>& font, int32_t fontSize)
{
    m_font = font;
    m_fontSize = fontSize;
    m_isDirty = true;
}

void UIText::SetFontSize(int32_t fontSize)
{
    m_fontSize = fontSize;
    m_isDirty = true;
}

void UIText::SetText(const std::string_view& text)
{
    m_text = text;
    m_isDirty = true;
}

void UIText::SetTextAlignment(TextAlignment textAlignment)
{
    m_textAlignment = textAlignment;
    m_isDirty = true;
}

void UIText::SetLineSpacing(float lineSpacing)
{
    m_lineSpacing = lineSpacing;
    m_isDirty = true;
}

void UIText::SetLineBreakMode(LineBreakMode lineBreakMode)
{
    m_lineBreakMode = lineBreakMode;
    m_isDirty = true;
}

void UIText::SetColor(const Color4f& color)
{
    m_color = color;
    m_isDirty = true;
}

std::shared_ptr<Font> UIText::GetFont() noexcept
{
    return m_font;
}

std::shared_ptr<const Font> UIText::GetFont() const noexcept
{
    return m_font;
}

int32_t UIText::GetFontSize() const noexcept
{
    return m_fontSize;
}

const std::string& UIText::GetText() const noexcept
{
    return m_text;
}

TextAlignment UIText::GetTextAlignment() const noexcept
{
    return m_textAlignment;
}

float UIText::GetLineSpacing() const noexcept
{
    return m_lineSpacing;
}

LineBreakMode UIText::GetLineBreakMode() const noexcept
{
    return m_lineBreakMode;
}

const Color4f& UIText::GetColor() const noexcept
{
    return m_color;
}

} /* namespace tgon */
