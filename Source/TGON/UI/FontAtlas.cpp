#include "PrecompiledHeader.h"

#include "FontAtlas.h"

namespace tgon
{

FontAtlas::FontAtlas(const std::shared_ptr<Font>& font) :
    m_font(font),
    m_textureAtlas(I32Extent2D(1024, 1024), PixelFormat::RGBA8888, 2)
{
}

FontAtlas::FontAtlas(std::shared_ptr<Font>&& font) :
    m_font(std::move(font)),
    m_textureAtlas(I32Extent2D(1024, 1024), PixelFormat::RGBA8888, 2)
{
}

FontAtlas::FontAtlas(FontAtlas&& rhs) noexcept :
    m_font(std::move(rhs.m_font)),
    m_textureAtlas(std::move(rhs.m_textureAtlas))
{
}

FontAtlas& FontAtlas::operator=(FontAtlas&& rhs) noexcept
{
    m_font = std::move(rhs.m_font);
    m_textureAtlas = std::move(rhs.m_textureAtlas);
    
    return *this;
}

void FontAtlas::Initialize(const std::shared_ptr<Font>& font)
{
    m_textureAtlas.Clear();
    m_font = font;
}

void FontAtlas::Initialize(std::shared_ptr<Font>&& font)
{
    m_textureAtlas.Clear();
    m_font = std::move(font);
}

std::optional<std::reference_wrapper<FRect>> FontAtlas::GetTextureRect(char32_t ch, int32_t fontSize) const
{
    auto textureAtlasKey = FontAtlas::CreateTextureAtlasKey(ch, fontSize);
    return m_textureAtlas.GetTextureRect(textureAtlasKey);
}

std::shared_ptr<const Texture> FontAtlas::GetAtlasTexture() const noexcept
{
    return m_textureAtlas.GetAtlasTexture();
}

std::shared_ptr<Texture> FontAtlas::GetAtlasTexture() noexcept
{
    return m_textureAtlas.GetAtlasTexture();
}

const FontFace& FontAtlas::GetFace(int32_t fontSize) const
{
    return m_font->GetFace(fontSize);
}

const GlyphData& FontAtlas::GetGlyphData(char32_t ch, int32_t fontSize) const
{
    decltype(auto) glyphData = m_font->GetGlyphData(ch, fontSize);
    
    auto textureAtlasKey = FontAtlas::CreateTextureAtlasKey(ch, fontSize);
    if (m_textureAtlas.Contains(textureAtlasKey) == false)
    {
        m_textureAtlas.Insert(textureAtlasKey, &glyphData.bitmap[0], glyphData.metrics.size);
    }
    
    return glyphData;
}

I32Vector2 FontAtlas::GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const
{
    return m_font->GetKerning(lhs, rhs, fontSize);
}

I32Extent2D FontAtlas::GetCharSize(char32_t ch, int32_t fontSize)
{
    return m_font->GetCharSize(ch, fontSize);
}

FontAtlas::TextureAtlasKey FontAtlas::CreateTextureAtlasKey(char32_t ch, int32_t fontSize) noexcept
{
    return static_cast<TextureAtlasKey>(ch) << 32 | fontSize;
}

} /* namespace tgon */
