#include "PrecompiledHeader.h"

#include <stdexcept>
#include <iostream>

#include "FontFactory.h"

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

#define TGON_FT_CHECK_ERROR(expr)\
{\
    FT_Error error = expr;\
    if (error)\
    {\
        throw std::runtime_error(GetFTErrorMessage(error));\
    }\
}

namespace
{

const struct
{
    int errorCode;
    const char* errorMessage;
} g_ftErrors[] =
#include FT_ERRORS_H

const char* GetFTErrorMessage(FT_Error error)
{
    return g_ftErrors[error].errorMessage;
}

} /* namespace */

namespace tgon
{


Font::Font(const StringHash& fontPath, FT_Library fontLibrary) :
    m_fontPath(fontPath),
    m_fontLibrary(fontLibrary),
    m_fontFace(nullptr)
{
    TGON_FT_CHECK_ERROR(FT_New_Face(fontLibrary, fontPath.CStr(), 0, &m_fontFace));   
    TGON_FT_CHECK_ERROR(FT_Select_Charmap(m_fontFace, FT_ENCODING_UNICODE));
}

const GlyphData& Font::GetGlyphData(char32_t character, int32_t size) const
{
    auto& characterTable = m_glyphDataCaches[character];
    auto iter = characterTable.find(size);
    if (iter != characterTable.end())
    {
        return iter->second;
    }
    
    TGON_FT_CHECK_ERROR(FT_Set_Pixel_Sizes(m_fontFace, 0, size));
    TGON_FT_CHECK_ERROR(FT_Load_Char(m_fontFace, character, FT_LOAD_RENDER));
    TGON_FT_CHECK_ERROR(FT_Render_Glyph(m_fontFace->glyph, FT_RENDER_MODE_NORMAL));
    
    int32_t bitmapWidth = m_fontFace->glyph->bitmap.width;
    int32_t bitmapHeight = m_fontFace->glyph->bitmap.rows;

    auto bitmap = std::make_unique<uint8_t[]>(bitmapWidth * bitmapHeight);
    memcpy(bitmap.get(), m_fontFace->glyph->bitmap.buffer, bitmapWidth * bitmapHeight);

    return characterTable.insert(iter, {size, GlyphData{
        character,
        I32Extent2D(static_cast<int32_t>(bitmapWidth), static_cast<int32_t>(bitmapHeight)),
        I32Vector2(static_cast<int32_t>(m_fontFace->glyph->bitmap_left), static_cast<int32_t>(m_fontFace->glyph->bitmap_top)),
        static_cast<int32_t>(m_fontFace->glyph->advance.x),
        std::move(bitmap)
    }})->second;
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

#undef FT_ERRORDEF
#undef FT_ERROR_START_LIST
#undef FT_ERROR_END_LIST
#undef TGON_FT_CHECK_ERROR