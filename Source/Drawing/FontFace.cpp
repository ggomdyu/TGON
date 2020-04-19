#include "PrecompiledHeader.h"

#include "FontFace.h"

namespace tg
{

FontFace::FontFace(FT_Face fontFace, int32_t fontSize) noexcept :
    m_fontFace(fontFace),
    m_fontSize(fontSize)
{
}

FontFace::FontFace(FontFace&& rhs) noexcept :
    m_fontFace(rhs.m_fontFace),
    m_fontSize(rhs.m_fontSize),
    m_glyphDatas(std::move(rhs.m_glyphDatas))
{
    rhs.m_fontFace = nullptr;
}

FontFace::~FontFace()
{
    if (m_fontFace != nullptr)
    {
        FT_Done_Face(m_fontFace);
        m_fontFace = nullptr;
    }
}

FontFace& FontFace::operator=(FontFace&& rhs) noexcept
{
    std::swap(m_fontFace, rhs.m_fontFace);
    std::swap(m_glyphDatas, rhs.m_glyphDatas);
    
    m_fontSize = rhs.m_fontSize;

    return *this;
}

std::shared_ptr<FontFace> FontFace::Create(const std::shared_ptr<FT_LibraryRec>& library, const std::vector<std::byte>& fileData, int32_t fontSize)
{
    FT_Face face = nullptr;
    FT_Error error = FT_New_Memory_Face(library.get(), reinterpret_cast<const FT_Byte*>(fileData.data()), static_cast<FT_Long>(fileData.size()), 0, &face);
    if (error)
    {
        return {};
    }

    error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
    if (error)
    {
        return {};
    }

    error = FT_Set_Pixel_Sizes(face, 0, fontSize);
    if (error)
    {
        return {};
    }

    return std::make_shared<FontFace>(face, fontSize);
}

const GlyphData* FontFace::GetGlyphData(char32_t ch) const
{
    auto iter = m_glyphDatas.find(ch);
    if (iter != m_glyphDatas.end())
    {
        return &iter->second;
    }

    FT_Error error = FT_Load_Char(m_fontFace, ch, FT_LOAD_RENDER);
    if (error)
    {
        return nullptr;
    }

    auto bitmapExtent = I32Extent2D(static_cast<int32_t>(m_fontFace->glyph->bitmap.width), static_cast<int32_t>(m_fontFace->glyph->bitmap.rows));

    auto bitmap = std::make_unique<std::byte[]>(bitmapExtent.width * bitmapExtent.height * 4);
    for (size_t i = 0, j = 0; i < bitmapExtent.width * bitmapExtent.height * 4; i += 4, ++j)
    {
        bitmap[i] = std::byte(255);
        bitmap[i + 1] = std::byte(255);
        bitmap[i + 2] = std::byte(255);
        bitmap[i + 3] = std::byte(m_fontFace->glyph->bitmap.buffer[j]);
    }

    auto bearing = I32Vector2(static_cast<int32_t>(m_fontFace->glyph->bitmap_left), static_cast<int32_t>(m_fontFace->glyph->bitmap_top));
    auto advance = I32Vector2(static_cast<int32_t>(m_fontFace->glyph->advance.x >> 6), static_cast<int32_t>(m_fontFace->glyph->advance.y >> 6));
    return &m_glyphDatas.insert(iter, {ch, GlyphData{ch, GlyphMetrics{bitmapExtent, bearing, advance}, std::move(bitmap)}})->second;
}

I32Vector2 FontFace::GetKerning(char32_t lhs, char32_t rhs) const
{
    auto lhsIndex = FT_Get_Char_Index(m_fontFace, lhs);
    auto rhsIndex = FT_Get_Char_Index(m_fontFace, rhs);
    FT_Vector kerning;
    auto error = FT_Get_Kerning(m_fontFace, lhsIndex, rhsIndex, FT_KERNING_DEFAULT, &kerning);
    if (error)
    {
        return {};
    }

    return I32Vector2(static_cast<int32_t>(kerning.x >> 6), static_cast<int32_t>(kerning.y >> 6));
}

}
