/**
 * @file    CanvasFontRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Math/Color.h"

#include "RendererComponent.h"

namespace tgon
{

class CanvasSprite;
class Texture;
class Font;

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

class TGON_API CanvasFontRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(CanvasFontRendererComponent);

/**@section Constructor */
public:
    using RendererComponent::RendererComponent;
    
    explicit CanvasFontRendererComponent(const std::shared_ptr<Material>& material);

/**@section Method */
public:
    virtual void Update() override;
    void SetFont(const std::shared_ptr<Font>& font) noexcept;
    void SetText(const std::string_view& text);
    void SetLineSpacing(float lineSpacing) noexcept;
    void SetLineBreakMode(LineBreakMode lineBreakMode) noexcept;
    void SetColor(const Color4f& color) noexcept;
    LineBreakMode GetLineBreakMode() const noexcept;
    const Color4f& GetColor() const noexcept;
    std::shared_ptr<const Font> GetFont() const noexcept;
    std::shared_ptr<Font> GetFont() noexcept;

private:
    void DrawTextToMainTexture();

/**@section Variable */
private:
    bool m_isDirty;
    std::string m_text;
    std::shared_ptr<CanvasSprite> m_sprite;
    std::shared_ptr<Texture> m_mainTexture;
    std::shared_ptr<Font> m_font;
    Color4f m_color;
    int32_t m_fontSize;
    float m_lineSpacing;
};

} /* namespace tgon */
