#include "PrecompiledHeader.h"

#include <stdexcept>

#include "FontFactory.h"

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

const struct
{
    int          errorCode;
    const char*  errorMessage;
} g_ftErrors[] =
#include FT_ERRORS_H

namespace tgon
{

//GlyphData::GlyphData(char32_t ch, FT_Face fontFace) noexcept :
//    m_ch(ch),
//    m_fontFace(fontFace)
//{
//}
//
//GlyphData::~GlyphData()
//{
//    if (m_fontFace != nullptr)
//    {
//        FT_Done_Face(m_fontFace);
//        m_fontFace = nullptr;
//    }
//}
//
//I32Extent2D GlyphData::GetSize() const noexcept
//{
//    auto width = static_cast<int32_t>(m_fontFace->glyph->bitmap.width);
//    auto height = static_cast<int32_t>(m_fontFace->glyph->bitmap.rows);
//
//    return {width, height};
//}
//
//I32Vector2 GlyphData::GetBearing() const noexcept
//{
//    auto x = static_cast<int32_t>(m_fontFace->glyph->bitmap_left);
//    auto y = static_cast<int32_t>(m_fontFace->glyph->bitmap_top);
//
//    return {x, y};
//}
//
//int32_t GlyphData::GetAdvance() const noexcept
//{
//    return static_cast<int32_t>(m_fontFace->glyph->advance.x);
//}
//
//uint8_t* GlyphData::GetImageData() noexcept
//{
//    return m_fontFace->glyph->bitmap.buffer;
//}
//
//char32_t GlyphData::GetCharacter() const noexcept
//{
//    return m_ch;
//}
//
//const uint8_t* GlyphData::GetImageData() const noexcept
//{
//    return m_fontFace->glyph->bitmap.buffer;
//}
    
Font::Font(const StringHash& fontPath, FT_Library fontLibrary) :
    m_fontPath(fontPath),
    m_fontLibrary(fontLibrary),
    m_fontFace(nullptr)
{
    FT_Error error = FT_New_Face(fontLibrary, fontPath.CStr(), 0, &m_fontFace);
    if (error)
    {
        throw std::runtime_error(g_ftErrors[error].errorMessage);
    }
    
    error = FT_Select_Charmap(m_fontFace, FT_ENCODING_UNICODE);
    if (error)
    {
        throw std::runtime_error(g_ftErrors[error].errorMessage);
    }
}

FontFactory::FontFactory() :
    m_fontLibrary(nullptr)
{
//    if (FT_Init_FreeType(&m_fontLibrary) != 0)
    {
        throw std::runtime_error("Failed to initialize FT_Library.");
    }
}

FontFactory::~FontFactory()
{
    if (m_fontLibrary != nullptr)
    {
//        FT_Done_FreeType(m_fontLibrary);
        m_fontLibrary = nullptr;
    }
}

std::shared_ptr<Font> FontFactory::GetFont(const StringHash& fontPath)
{
    auto iter = m_fonts.find(fontPath);
    if (iter != m_fonts.end())
    {
        return iter->second;
    }

    auto font = std::make_shared<Font>(fontPath, m_fontLibrary);
    m_fonts.insert(iter, {fontPath, font});

    return font;
}

} /* namespace tgon */
