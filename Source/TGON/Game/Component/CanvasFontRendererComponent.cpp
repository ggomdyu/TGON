#include "PrecompiledHeader.h"

#include "Game/GameObject.h"
#include "Engine/GraphicsModule.h"

#include "CanvasFontRendererComponent.h"

namespace tgon
{

CanvasFontRendererComponent::CanvasFontRendererComponent(const std::shared_ptr<Material>& material) :
    RendererComponent(material),
    m_lineSpacing(0.0f),
    m_fontSize(0)
{
}
    
void CanvasFontRendererComponent::Update()
{
}

void CanvasFontRendererComponent::SetFont(const std::shared_ptr<Font>& font) noexcept
{
    m_font = font;
    m_isDirty = true;
}

void CanvasFontRendererComponent::SetText(const std::string_view& text)
{
    m_isDirty = true;
}

void CanvasFontRendererComponent::SetLineSpacing(float lineSpacing) noexcept
{
    m_lineSpacing = lineSpacing;
    m_isDirty = true;
}

void CanvasFontRendererComponent::SetLineBreakMode(LineBreakMode lineBreakMode) noexcept
{
    m_isDirty = true;
}

void CanvasFontRendererComponent::SetColor(const Color4f& color)
{
    m_color = color;
    m_isDirty = true;
}

LineBreakMode CanvasFontRendererComponent::GetLineBreakMode() const noexcept
{
    return LineBreakMode();
}

const Color4f& CanvasFontRendererComponent::GetColor() const noexcept
{
    return m_color;
}

std::shared_ptr<const Font> CanvasFontRendererComponent::GetFont() const noexcept
{
    return m_font;
}

std::shared_ptr<Font> CanvasFontRendererComponent::GetFont() noexcept
{
    return m_font;
}

void CanvasFontRendererComponent::DrawTextToMainTexture()
{
    //float accumulatedXPos = -100.0f;
    //float accumulatedYPos = 0.0f;
    //const wchar_t str[] = L"Hello.My name is Junho";
    //for (int i = 0; i < std::extent<decltype(str)>::value - 1; ++i)
    //{
    //    int32_t fontSize = 30;
    //    auto& glyphData = font->GetGlyphData(str[i], fontSize);
    //
    //    if (i != 0)
    //    {
    //        auto& prevGlyphData = font->GetGlyphData( str[i - 1], fontSize );
    //        accumulatedXPos -= (prevGlyphData.size.width - glyphData.size.width) / 2;
    //
    //        auto kerning = font->GetKerning( str[i - 1], str[i], fontSize );
    //        accumulatedXPos += kerning.x;
    //    }
    //
    //    float xPos = accumulatedXPos + glyphData.bearing.x;
    //    float yPos = accumulatedYPos - glyphData.size.height / 2 + glyphData.bearing.y;
    //
    //    auto object = std::make_shared<GameObject>("introSprite1", new Transform());
    //    object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    //    object->GetTransform()->SetLocalPosition(Vector3( xPos, yPos, 0.0f ));
    //    auto spriteComponent = object->AddComponent<CanvasSpriteRendererComponent>();
    //    auto texture = std::make_shared<Texture>(&glyphData.bitmap[0], glyphData.size, PixelFormat::R8, FilterMode::Point, WrapMode::Clamp, false, false);
    //    spriteComponent->SetSprite(std::make_shared<CanvasSprite>(texture));
    //    this->AddObject(object);
    //
    //    accumulatedXPos += glyphData.advance.x;
    //}
}

} /* namespace tgon */
