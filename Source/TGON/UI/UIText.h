/**
 * @file    UIText.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include <string>

#include "Graphics/Texture.h"
#include "Math/Color.h"
#include "Drawing/Font.h"

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

class TGON_API UIText final
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
    std::shared_ptr<Font> GetFont() noexcept;
    std::shared_ptr<const Font> GetFont() const noexcept;
    int32_t GetFontSize() const noexcept;
    const std::string& GetText() const noexcept;
    TextAlignment GetTextAlignment() const noexcept;
    float GetLineSpacing() const noexcept;
    LineBreakMode GetLineBreakMode() const noexcept;
    const Color4f& GetColor() const noexcept;
    
private:
    
    
/**@section Variable */
private:
    bool m_isDirty = true;
    std::string m_text;
    std::shared_ptr<Font> m_font;
    int32_t m_fontSize = 0;
    TextAlignment m_textAlignment = TextAlignment::UpperLeft;
    float m_lineSpacing = 0.0f;
    LineBreakMode m_lineBreakMode = LineBreakMode::Clip;
    Color4f m_color;
};

} /* namespace tgon */
