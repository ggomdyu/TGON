/**
 * @file    TextRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Math/Color.h"
#include "UI/UIText.h"

#include "RendererComponent.h"

namespace tgon
{

class TextRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(TextRendererComponent)

/**@section Constructor */
public:
    TextRendererComponent();
    
/**@section Method */
public:
    void SetFont(const char* fontPath);
    void SetFont(const std::shared_ptr<UIFont>& font) noexcept;
    void SetFontSize(int32_t fontSize) noexcept;
    void SetText(const std::string_view& text);
    void SetLineSpacing(float lineSpacing) noexcept;
    void SetLineBreakMode(LineBreakMode lineBreakMode) noexcept;
    void SetTextAlignment(TextAlignment textAlignment) noexcept;
    void SetColor(const Color4f& color) noexcept;
    void SetRect(const I32Rect& rect) noexcept;
    void SetSortingLayer(int32_t sortingLayer) noexcept;
    LineBreakMode GetLineBreakMode() const noexcept;
    TextAlignment GetTextAlignment() const noexcept;
    const Color4f& GetColor() const noexcept;
    std::shared_ptr<const UIFont> GetFont() const noexcept;
    int32_t GetFontSize() const noexcept;
    std::shared_ptr<UIFont> GetFont() noexcept;
    const I32Rect& GetRect() const noexcept;
    int32_t GetSortingLayer() const noexcept;
    void Update() override;
    
/**@section Variable */
private:
    std::shared_ptr<UIText> m_text;
    int32_t m_sortingLayer = 0;
};

} /* namespace tgon */
