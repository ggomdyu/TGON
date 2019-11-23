#include "PrecompiledHeader.h"

#include "Engine/AssetModule.h"
#include "Platform/Application.h"
#include "Text/Encoding.h"

#include "UIText.h"

namespace tgon
{

TextBlock::TextBlock(const gsl::span<const char32_t>& characters, const std::shared_ptr<Font>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept :
    m_rect(rect),
    m_contentRect(rect.x, rect.y, 0, 0)
{
    // TODO: First of all, we must check whether the text spill over.

    int32_t accumulatedBlockHeight = 0;
    gsl::span<const char32_t> charactersSpan = characters;
    while (true)
    {
        bool isTextSpillOver = accumulatedBlockHeight > rect.height;
        if (isTextSpillOver)
        {
            this->PopBackLine();
            break;
        }

        m_lineInfos.push_back(LineInfo{0, 0, I32Rect(rect.x, rect.y - accumulatedBlockHeight, 0, 0)});

        int32_t insertedCharacterLen = this->TryAddTextLine(charactersSpan, font, fontSize, rect);
        if (insertedCharacterLen == 0)
        {
            this->PopBackLine();
            break;
        }

        accumulatedBlockHeight += m_lineInfos.back().contentRect.height;
        charactersSpan = charactersSpan.subspan(insertedCharacterLen);
    }
    
    // The default text alignment mode is upper left, so if the desired text alignment mode is the same, then ignore the realignment.
    if (textAlignment != TextAlignment::UpperLeft)
    {
        this->ProcessTextAlignment(textAlignment);
    }
}

const I32Rect& TextBlock::GetRect() const noexcept
{
    return m_rect;
}

const I32Rect& TextBlock::GetContentRect() const noexcept
{
    return m_contentRect;
}

const std::vector<TextBlock::CharacterInfo>& TextBlock::GetCharacterInfos() const noexcept
{
    return m_characterInfos;
}

void TextBlock::PopBackLine()
{
    if (m_lineInfos.empty())
    {
        return;
    }
    
    auto& backLineInfo = m_lineInfos.back();
    m_characterInfos.erase(m_characterInfos.begin() + backLineInfo.characterStartIndex, m_characterInfos.begin() + backLineInfo.characterEndIndex);
    m_contentRect.height -= backLineInfo.contentRect.height;
    m_lineInfos.pop_back();
}

int32_t TextBlock::TryAddTextLine(const gsl::span<const char32_t>& characters, const std::shared_ptr<Font>& font, int32_t fontSize, const I32Rect& rect)
{
    int32_t yMin = INT32_MAX;
    int32_t yMax = -INT32_MAX;
    int32_t yMaxBearing = -INT32_MAX;
    int32_t insertedTextLen = static_cast<int32_t>(characters.size());
    int32_t characterStartIndex = m_iterIndex;
    int32_t xAdvance = 0;
    
    auto& lineInfo = m_lineInfos.back();
    
    for (size_t i = 0; i < characters.size(); ++i)
    {
        auto ch = characters[i];
        
        const auto& glyphData = font->GetGlyphData(ch, fontSize);
        if (rect.width < xAdvance + glyphData.metrics.size.width)
        {
            insertedTextLen = static_cast<int32_t>(i);
            break;
        }

        I32Vector2 characterPos{rect.x + xAdvance + glyphData.metrics.bearing.x, rect.y + glyphData.metrics.bearing.y - m_contentRect.height};
        m_characterInfos.push_back({glyphData.ch, {characterPos.x, characterPos.y, glyphData.metrics.size.width, glyphData.metrics.size.height}});
        
        yMin = std::min(yMin, characterPos.y - glyphData.metrics.size.height);
        yMax = std::max(yMax, characterPos.y);
        yMaxBearing = std::max(yMaxBearing, glyphData.metrics.bearing.y);
        
        xAdvance += glyphData.metrics.advance.x;
        m_iterIndex += 1;
    }

    if (insertedTextLen > 0)
    {
        lineInfo.characterStartIndex = characterStartIndex;
        lineInfo.characterEndIndex = m_iterIndex;
        
        // Refresh the content rect of line
        int32_t lineHeight = yMax - yMin;
        const auto& frontCharacterInfo = m_characterInfos[lineInfo.characterStartIndex];
        const auto& backCharacterInfo = m_characterInfos[std::max(lineInfo.characterStartIndex, lineInfo.characterEndIndex - 1)];
        lineInfo.contentRect.height = lineHeight;
        lineInfo.contentRect.width = (backCharacterInfo.rect.x + backCharacterInfo.rect.width) - frontCharacterInfo.rect.x;
        
        // Refresh the content rect of total text block
        m_contentRect.height += lineHeight;
        m_contentRect.width = std::max(m_contentRect.width, lineInfo.contentRect.width);
    
        for (int32_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
        {
            m_characterInfos[i].rect.y -= yMaxBearing;
        }
    }
    
    return insertedTextLen;
}

void TextBlock::ProcessTextAlignment(TextAlignment textAlignment)
{
    switch (textAlignment)
    {
    case TextAlignment::LowerLeft:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::LowerCenter:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::LowerRight:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::MiddleLeft:
        {
            int32_t yOffset = m_rect.y - ((m_rect.height - m_contentRect.height) / 2);
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::MiddleCenter:
        {
            int32_t yOffset = m_rect.y - (m_rect.height - m_contentRect.height) / 2;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::MiddleRight:
        {
            int32_t yOffset = m_rect.y - ((m_rect.height - m_contentRect.height) / 2);
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::UpperLeft:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::UpperCenter:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::UpperRight:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
    }
}

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
    m_characters = Encoding::UTF8().GetChars(reinterpret_cast<const std::byte*>(&text[0]), static_cast<int32_t>(text.length()));
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

void UIText::SetRect(const I32Rect& rect)
{
    m_rect = rect;
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

const I32Rect& UIText::GetRect() const noexcept
{
    return m_rect;
}

const std::vector<TextBlock::CharacterInfo>& UIText::GetCharacterInfos() const noexcept
{
    if (m_isDirty)
    {
        m_textBlock = TextBlock(m_characters, m_font, m_fontSize, m_rect, m_lineBreakMode, m_textAlignment);
        m_isDirty = false;
    }
    
    return m_textBlock.GetCharacterInfos();
}

} /* namespace tgon */
