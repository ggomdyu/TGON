/**
 * @file    UIText.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include <string>
#include <shared_mutex>

#include "Drawing/Font.h"
#include "Graphics/TextureAtlas.h"
#include "Math/Color.h"
#include "Math/Rect.h"

#include "UIElement.h"
#include "UIFont.h"

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
    CharacterWrap,
    TruncateHead,
    TruncateMiddle,
    TruncateTail,
};

class UIText :
    public UIElement
{
/**@section Struct */
public:
    struct CharacterInfo
    {
        char32_t character;
        I32Rect rect;
    };
    
/**@section Enum */
private:
    enum : int32_t { DefaultFontSize = 12 };

/**@section Constructor */
public:
    UIText() noexcept;
    UIText(UIText&& rhs) noexcept;

/**@section Destructor */
public:
    ~UIText();
    
/**@section Operator */
public:
    UIText& operator=(UIText&& rhs) noexcept;
    
/**@section Method */
public:
    void SetFont(const std::shared_ptr<UIFont>& font);
    void SetFontSize(int32_t fontSize);
    void SetText(const std::string_view& text);
    void SetTextAlignment(TextAlignment textAlignment);
    void SetLineSpacing(float lineSpacing);
    void SetLineBreakMode(LineBreakMode lineBreakMode);
    void SetColor(const Color4f& color);
    void SetRect(const I32Rect& rect);
    std::shared_ptr<UIFont> GetFont() noexcept;
    std::shared_ptr<const UIFont> GetFont() const noexcept;
    int32_t GetFontSize() const noexcept;
    const std::string& GetText() const noexcept;
    TextAlignment GetTextAlignment() const noexcept;
    float GetLineSpacing() const noexcept;
    LineBreakMode GetLineBreakMode() const noexcept;
    const Color4f& GetColor() const noexcept;
    const I32Rect& GetRect() const noexcept;
    const I32Rect& GetContentRect() const noexcept;
    const std::vector<CharacterInfo>& GetCharacterInfos() const noexcept;
    void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const;
    
/**@section Variable */
private:
    std::string m_text;
    std::shared_ptr<UIFont> m_font;
    int32_t m_fontSize = DefaultFontSize;
    TextAlignment m_textAlignment = TextAlignment::UpperLeft;
    float m_lineSpacing = 0.0f;
    LineBreakMode m_lineBreakMode = LineBreakMode::CharacterWrap;
    Color4f m_color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    I32Rect m_rect;
    mutable bool m_isDirty = true;
    std::unique_ptr<class TextBlock> m_textBlock;
};

} /* namespace tgon */
