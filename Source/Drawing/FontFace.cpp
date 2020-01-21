#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"

#include "FontFace.h"

namespace tgon
{

extern const char* ConvertFTErrorToString(FT_Error error);

FontFace::FontFace(FT_Face fontFace, int32_t fontSize) noexcept :
    m_fontFace(fontFace),
    m_fontSize(fontSize)
{
}

FontFace::FontFace(FontFace&& rhs) noexcept :
    m_fontSize(rhs.m_fontSize),
    m_fontFace(rhs.m_fontFace),
    m_glyphDatas(std::move(rhs.m_glyphDatas))
{
    rhs.m_fontFace = nullptr;
}

FontFace::~FontFace()
{
    this->Destroy();
}

FontFace& FontFace::operator=(FontFace&& rhs) noexcept
{
    m_fontSize = rhs.m_fontSize;

    std::swap(m_fontFace, rhs.m_fontFace);
    std::swap(m_glyphDatas, rhs.m_glyphDatas);

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

const GlyphData& FontFace::GetGlyphData(char32_t ch) const
{
    auto iter = m_glyphDatas.find(ch);
    if (iter != m_glyphDatas.end())
    {
        return iter->second;
    }

    FT_Error error = FT_Load_Char(m_fontFace, ch, FT_LOAD_RENDER);
    if (error)
    {
        Debug::Fail("Failed to invoke FT_Load_Char.", ConvertFTErrorToString(error));
    }

    auto bitmapWidth = static_cast<size_t>(m_fontFace->glyph->bitmap.width);
    auto bitmapHeight = static_cast<size_t>(m_fontFace->glyph->bitmap.rows);

    auto bitmap = std::make_unique<std::byte[]>(bitmapWidth * bitmapHeight * 4);
    for (size_t i = 0, j = 0; i < bitmapWidth * bitmapHeight * 4; i += 4, ++j)
    {
        bitmap[i] = std::byte(255);
        bitmap[i + 1] = std::byte(255);
        bitmap[i + 2] = std::byte(255);
        bitmap[i + 3] = std::byte(m_fontFace->glyph->bitmap.buffer[j]);
    }

    return m_glyphDatas.insert(iter, {ch, GlyphData{
        ch,
        GlyphMetrics{
            I32Extent2D(static_cast<int32_t>(bitmapWidth), static_cast<int32_t>(bitmapHeight)), 
            I32Vector2(static_cast<int32_t>(m_fontFace->glyph->bitmap_left), static_cast<int32_t>(m_fontFace->glyph->bitmap_top)),
            I32Vector2(static_cast<int32_t>(m_fontFace->glyph->advance.x >> 6), static_cast<int32_t>(m_fontFace->glyph->advance.y >> 6))
        },
        std::move(bitmap)
    }})->second;
}

I32Vector2 FontFace::GetKerning(char32_t lhs, char32_t rhs) const
{
    auto lhsIndex = FT_Get_Char_Index(m_fontFace, lhs);
    auto rhsIndex = FT_Get_Char_Index(m_fontFace, rhs);
    FT_Vector kerning;
    auto error = FT_Get_Kerning(m_fontFace, lhsIndex, rhsIndex, FT_KERNING_DEFAULT, &kerning);
    if (error)
    {
        Debug::Fail("Failed to invoke FT_Get_Kerning.", ConvertFTErrorToString(error));
    }

    return I32Vector2(static_cast<int32_t>(kerning.x >> 6), static_cast<int32_t>(kerning.y >> 6));
}

void FontFace::Destroy()
{
    if (m_fontFace != nullptr)
    {
        FT_Done_Face(m_fontFace);
        m_fontFace = nullptr;
    }
}

} /* namespace tgon */
