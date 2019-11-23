/**
 * @file    UIText.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include <string>
#include <shared_mutex>

#include "Drawing/Font.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include "Core/NonCopyable.h"

#include "UISpriteBatch.h"

namespace tgon
{

enum class TextAlignment
{
    UpperLeft,
    UpperCenter,
    UpperRight,
    MiddleLeft,
    MiddleCenter,
    MiddleRight,
    LowerLeft,
    LowerCenter,
    LowerRight
};

enum class LineBreakMode
{
    Clip,
    TruncateHead,
    TruncateMiddle,
    TruncateTail,
};

//class UIAtlasFont :
//    public Font
//{
//public:
//    TextureAtlas m_textureAtlas;
//}

class TextBlock
{
/**@section Struct */
public:
    struct CharacterInfo
    {
        char32_t character;
        I32Rect rect;
    };
    
    struct LineInfo
    {
        int32_t characterStartIndex;
        int32_t characterEndIndex;
        I32Rect contentRect;
    };
    
/**@section Constructor */
public:
    TextBlock() = default;
    TextBlock(const gsl::span<const char32_t>& characters, const std::shared_ptr<Font>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept;
    
/**@section Method */
public:
    const I32Rect& GetRect() const noexcept;
    const I32Rect& GetContentRect() const noexcept;
    const std::vector<CharacterInfo>& GetCharacterInfos() const noexcept;
    
private:
    void PopBackLine();
    void ProcessConstructTextLines();
    void ProcessLineBreakMode(LineBreakMode lineBreakMode);
    void ProcessTextAlignment(TextAlignment textAlignment);
    
    int32_t TryAddTextLine(const gsl::span<const char32_t>& characters, const std::shared_ptr<Font>& font, int32_t fontSize, const I32Rect& rect);
    
/**@section Variable */
private:
    I32Rect m_rect;
    I32Rect m_contentRect;
    std::vector<CharacterInfo> m_characterInfos;
    std::vector<LineInfo> m_lineInfos;
    int32_t m_iterIndex = 0;
};

class UIText final :
    private NonCopyable
{
/**@section Enum */
public:
    enum : int32_t { DefaultFontSize = 12 };

/**@section Constructor */
public:
    UIText() noexcept = default;
    
/**@section Method */
public:
    void SetFont(const char* fontPath, int32_t fontSize = DefaultFontSize);
    void SetFont(const std::shared_ptr<Font>& font, int32_t fontSize = DefaultFontSize);
    void SetFontSize(int32_t fontSize);
    void SetText(const std::string_view& text);
    void SetTextAlignment(TextAlignment textAlignment);
    void SetLineSpacing(float lineSpacing);
    void SetLineBreakMode(LineBreakMode lineBreakMode);
    void SetColor(const Color4f& color);
    void SetRect(const I32Rect& rect);
    std::shared_ptr<Font> GetFont() noexcept;
    std::shared_ptr<const Font> GetFont() const noexcept;
    int32_t GetFontSize() const noexcept;
    const std::string& GetText() const noexcept;
    TextAlignment GetTextAlignment() const noexcept;
    float GetLineSpacing() const noexcept;
    LineBreakMode GetLineBreakMode() const noexcept;
    const Color4f& GetColor() const noexcept;
    const I32Rect& GetRect() const noexcept;
    const I32Rect& GetContentRect() const noexcept;
    const std::vector<TextBlock::CharacterInfo>& GetCharacterInfos() const noexcept;

/**@section Variable */
private:
    std::string m_text;
    std::vector<char32_t> m_characters;
    std::shared_ptr<Font> m_font;
    int32_t m_fontSize = 0;
    TextAlignment m_textAlignment = TextAlignment::UpperLeft;
    float m_lineSpacing = 0.0f;
    LineBreakMode m_lineBreakMode = LineBreakMode::Clip;
    Color4f m_color;
    I32Rect m_rect;
    mutable bool m_isDirty = true;
    mutable TextBlock m_textBlock;
};

} /* namespace tgon */
