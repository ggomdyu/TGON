#include "PrecompiledHeader.h"

#include "UIFont.h"

namespace tgon
{

UIFont::UIFont(Font&& font) :
    m_font(std::move(font)),
    m_textureAtlas(I32Extent2D(1024, 1024), PixelFormat::RGBA8888, 2)

{
}

UIFont::UIFont(UIFont&& rhs) noexcept :
    m_font(std::move(rhs.m_font)),
    m_textureAtlas(std::move(rhs.m_textureAtlas))
{
}

UIFont& UIFont::operator=(UIFont&& rhs) noexcept
{
    m_font = std::move(rhs.m_font);
    m_textureAtlas = std::move(rhs.m_textureAtlas);
    
    return *this;
}

void UIFont::Insert(char32_t ch, int32_t fontSize)
{
    const auto& glyphData = m_font.GetGlyphData(ch, fontSize);
    m_textureAtlas.Insert(ch, &glyphData.bitmap[0], glyphData.metrics.size);
}

void UIFont::Insert(const gsl::span<char32_t>& characters, int32_t fontSize)
{
    for (auto ch : characters)
    {
        const auto& glyphData = m_font.GetGlyphData(ch, fontSize);
        m_textureAtlas.Insert(ch, &glyphData.bitmap[0], glyphData.metrics.size);
    }
}

std::optional<std::reference_wrapper<FRect>> UIFont::GetTextureRect(size_t key) const
{
    return m_textureAtlas.GetTextureRect(key);
}

std::shared_ptr<const Texture> UIFont::GetAtlasTexture() const noexcept
{
    return m_textureAtlas.GetAtlasTexture();
}

std::shared_ptr<Texture> UIFont::GetAtlasTexture() noexcept
{
    return m_textureAtlas.GetAtlasTexture();
}

const FontFace& UIFont::GetFace(int32_t fontSize) const
{
    return m_font.GetFace(fontSize);
}

const GlyphData& UIFont::GetGlyphData(char32_t ch, int32_t fontSize) const
{
    return m_font.GetGlyphData(ch, fontSize);
}

I32Vector2 UIFont::GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const
{
    return m_font.GetKerning(lhs, rhs, fontSize);
}

I32Extent2D UIFont::GetTextSize(int32_t fontSize)
{
    return m_font.GetTextSize(fontSize);
}

I32Extent2D UIFont::GetTextSize(int32_t fontSize, const I32Extent2D& rect) const
{
    return m_font.GetTextSize(fontSize, rect);
}

} /* namespace tgon */
