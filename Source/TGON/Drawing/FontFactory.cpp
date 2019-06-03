#include "PrecompiledHeader.h"

#include <stdexcept>

#include "FontFactory.h"

namespace tgon
{

GlyphData::GlyphData(char32_t ch, FT_Face fontFace) noexcept :
    m_ch(ch),
    m_fontFace(fontFace)
{
}

GlyphData::~GlyphData()
{
    if (m_fontFace != nullptr)
    {
        FT_Done_Face(m_fontFace);
        m_fontFace = nullptr;
    }
}

I32Extent2D GlyphData::GetSize() const noexcept
{
    auto width = static_cast<int32_t>(m_fontFace->glyph->bitmap.width);
    auto height = static_cast<int32_t>(m_fontFace->glyph->bitmap.rows);

    return {width, height};
}

I32Vector2 GlyphData::GetBearing() const noexcept
{
    auto x = static_cast<int32_t>(m_fontFace->glyph->bitmap_left);
    auto y = static_cast<int32_t>(m_fontFace->glyph->bitmap_top);

    return {x, y};
}

int32_t GlyphData::GetAdvance() const noexcept
{
    return static_cast<int32_t>(m_fontFace->glyph->advance.x);
}

uint8_t* GlyphData::GetImageData() noexcept
{
    return m_fontFace->glyph->bitmap.buffer;
}

char32_t GlyphData::GetCharacter() const noexcept
{
    return m_ch;
}

const uint8_t* GlyphData::GetImageData() const noexcept
{
    return m_fontFace->glyph->bitmap.buffer;
}

FontFactory::FontFactory() :
    m_fontLibrary(nullptr)
{
    if (FT_Init_FreeType(&m_fontLibrary) != 0)
    {
        throw std::runtime_error("Failed to initialize FT_Library.");
    }
}

FontFactory::~FontFactory()
{
    if (m_fontLibrary != nullptr)
    {
        FT_Done_FreeType(m_fontLibrary);
        m_fontLibrary = nullptr;
    }
}

FT_Face FontFactory::ImportFont(const StringHash& fontPath)
{
    auto& fontFace = m_fontFaces[fontPath];
    if (fontFace != nullptr)
    {
        return fontFace;
    }

    if (FT_New_Face(m_fontLibrary, fontPath.CStr(), 0, &fontFace) != 0)
    {
        return nullptr;
    }


    return fontFace;
}

} /* namespace tgon */
