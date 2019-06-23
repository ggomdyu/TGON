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

constexpr int32_t ConvertFTPixelModeToBits(FT_Pixel_Mode pixelMode)
{
    constexpr int32_t bytesTable[] =
    {
        1, // FT_PIXEL_MODE_MONO
        8, // FT_PIXEL_MODE_GRAY
        2, // FT_PIXEL_MODE_GRAY2
        4, // FT_PIXEL_MODE_GRAY4
        8, // FT_PIXEL_MODE_LCD
        8, // FT_PIXEL_MODE_LCD_V
        32, // FT_PIXEL_MODE_BGRA
    };

    return bytesTable[static_cast<int>(pixelMode)];
}

} /* namespace */

namespace tgon
{

FontFace::FontFace(const uint8_t* fileData, std::size_t fileDataBytes, FT_Library library, FontSize fontSize) :
    m_fontSize(fontSize),
    m_fontFace([&]()
    {
        FT_Face face = nullptr;
        TGON_FT_CHECK_ERROR(FT_New_Memory_Face(library, fileData, fileDataBytes, 0, &face));
        TGON_FT_CHECK_ERROR(FT_Select_Charmap(face, FT_ENCODING_UNICODE));
        TGON_FT_CHECK_ERROR(FT_Set_Pixel_Sizes(face, 0, fontSize));

        return face;
    } ())
{
}

FontFace::FontFace(FontFace&& rhs) noexcept :
    m_glyphDatas(std::move(rhs.m_glyphDatas)),
    m_fontFace(rhs.m_fontFace),
    m_fontSize(rhs.m_fontSize)
{
    rhs.m_fontFace = nullptr;
    rhs.m_fontSize = 0;
}

FontFace& FontFace::operator=(FontFace&& rhs) noexcept
{
    m_glyphDatas = std::move(rhs.m_glyphDatas);
    m_fontFace = rhs.m_fontFace;
    m_fontSize = rhs.m_fontSize;
     
    rhs.m_fontFace = nullptr;
    rhs.m_fontSize = 0;

    return *this;
}

const GlyphData& FontFace::GetGlyphData(char32_t character) const
{
    auto iter = m_glyphDatas.find(character);
    if (iter != m_glyphDatas.end())
    {
        return iter->second;
    }
    
    TGON_FT_CHECK_ERROR(FT_Load_Char(m_fontFace, character, FT_LOAD_RENDER));

    int32_t bitmapWidth = m_fontFace->glyph->bitmap.width;
    int32_t bitmapHeight = m_fontFace->glyph->bitmap.rows;

    auto bitmap = std::make_unique<uint8_t[]>((bitmapWidth * bitmapHeight));
    memcpy(bitmap.get(), m_fontFace->glyph->bitmap.buffer, bitmapWidth * bitmapHeight);

    return m_glyphDatas.insert(iter, {character, GlyphData{
        character,
        I32Extent2D(static_cast<int32_t>(bitmapWidth), static_cast<int32_t>(bitmapHeight)),
        I32Vector2(static_cast<int32_t>(m_fontFace->glyph->bitmap_left), static_cast<int32_t>(m_fontFace->glyph->bitmap_top)),
        static_cast<int32_t>(m_fontFace->glyph->advance.x),
        std::move(bitmap)
    }})->second;
}

Font::Font(const StringHash& fontPath, FT_Library library) :
    Font([&]() -> Font
    {
#if defined(_MSC_VER) && _MSC_VER >= 1400
        FILE * file = nullptr;
        fopen_s(&file, fontPath.CStr(), "rb");
#else
        FILE* file = fopen(filePath, "rb");
#endif
        if (file == nullptr)
        {
            return Font(nullptr, 0, library);
        }

        fseek(file, 0, SEEK_END);
        int32_t fileDataBytes = static_cast<int32_t>(ftell(file));
        fseek(file, 0, SEEK_SET);

        auto fileData = new uint8_t[fileDataBytes];
        fread(fileData, 1, fileDataBytes, file);
        fclose(file);

        return Font(fileData, fileDataBytes, library);
    } ())
{
}

Font::Font(uint8_t* fileData, std::size_t fileDataBytes, FT_Library library) :
    m_fileData(fileData),
    m_fileDataBytes(fileDataBytes),
    m_library(library)
{
}

Font::Font(Font&& rhs) :
    m_fileData(std::move(rhs.m_fileData)),
    m_fileDataBytes(rhs.m_fileDataBytes),
    m_library(rhs.m_library),
    m_fontFaces(std::move(rhs.m_fontFaces))
{
    rhs.m_fileDataBytes = 0;
    rhs.m_library = nullptr;
}

const FontFace& Font::GetFace(FontSize fontSize) const
{
    auto iter = m_fontFaces.find(fontSize);
    if (iter != m_fontFaces.end())
    {
        return iter->second;
    }
;
    return m_fontFaces.insert(iter, {fontSize, FontFace(m_fileData.get(), m_fileDataBytes, m_library, size)})->second;
}

const GlyphData& Font::GetGlyphData(char32_t character, FontSize fontSize) const
{
    return this->GetFace(fontSize).GetGlyphData(character);
}

FontFactory::FontFactory() :
    m_library(nullptr)
{
    if (FT_Init_FreeType(&m_library) != 0)
    {
        throw std::runtime_error("Failed to initialize FT_Library.");
    }
}

FontFactory::~FontFactory()
{
    if (m_library != nullptr)
    {
        FT_Done_FreeType(m_library);
        m_library = nullptr;
    }
}

std::shared_ptr<Font> FontFactory::GetFont(const StringHash& fontPath)
{
    auto iter = m_fonts.find(fontPath);
    if (iter != m_fonts.end())
    {
        return iter->second;
    }

    auto font = std::make_shared<Font>(fontPath, m_library);
    m_fonts.insert(iter, {fontPath, font});

    return font;
}

} /* namespace tgon */

#undef FT_ERRORDEF
#undef FT_ERROR_START_LIST
#undef FT_ERROR_END_LIST
#undef TGON_FT_CHECK_ERROR