#include "PrecompiledHeader.h"

#include <stdexcept>

#include "Diagnostics/Debug.h"

#include "FontFactory.h"

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  {e, s},
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       {0, 0 }};

namespace
{

const struct
{
    int errorCode;
    const char* errorMessage;
} g_ftErrors[] =
#include FT_ERRORS_H

const char* ConvertFTErrorToString(FT_Error error)
{
    return g_ftErrors[error].errorMessage;
}

constexpr int32_t ConvertFTPixelModeToBits(FT_Pixel_Mode pixelMode) noexcept
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

    return bytesTable[static_cast<int32_t>(pixelMode)];
}

} /* namespace */

namespace tgon
{

FontFace::FontFace(const std::byte* fileData, std::size_t fileDataBytes, FT_Library library, FontSize fontSize) :
    m_fontSize(fontSize),
    m_fontFace([&]() -> FT_Face
    {
        FT_Face face = nullptr;
        FT_Error error = FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(fileData), fileDataBytes, 0, &face);
        if (error)
        {
            Debug::Fail("Failed to invoke FT_New_Memory_Face.", ConvertFTErrorToString(error));
        }

        error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (error)
        {
            Debug::Fail("Failed to invoke FT_Select_Charmap.", ConvertFTErrorToString(error));
        }

        error = FT_Set_Pixel_Sizes(face, 0, fontSize);
        if (error)
        {
            Debug::Fail("Failed to invoke FT_Set_Pixel_Sizes.", ConvertFTErrorToString(error));
        }

        return face;
    } ())
{
}

FontFace::FontFace(FontFace&& rhs) noexcept :
    m_fontSize(rhs.m_fontSize),
    m_fontFace(rhs.m_fontFace),
    m_glyphDatas(std::move(rhs.m_glyphDatas))
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

const GlyphData& FontFace::GetGlyphData(UnicodeScalar ch) const
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

    int32_t bitmapWidth = m_fontFace->glyph->bitmap.width;
    int32_t bitmapHeight = m_fontFace->glyph->bitmap.rows;

    auto bitmap = std::make_unique<std::byte[]>((bitmapWidth * bitmapHeight * 4));
    for (int i = 0, j = 0; i < bitmapWidth * bitmapHeight * 4; i += 4, ++j)
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

I32Vector2 FontFace::GetKerning(UnicodeScalar lhs, UnicodeScalar rhs) const
{
    FT_Vector kerning;
    auto lhsIndex = FT_Get_Char_Index(m_fontFace, lhs);
    auto rhsIndex = FT_Get_Char_Index(m_fontFace, rhs);
    auto error = FT_Get_Kerning(m_fontFace, lhsIndex, rhsIndex, FT_KERNING_DEFAULT, &kerning);
    if (error)
    {
        Debug::Fail("Failed to invoke FT_Get_Kerning.", ConvertFTErrorToString(error));
    }

    return I32Vector2(static_cast<int32_t>(kerning.x >> 6), static_cast<int32_t>(kerning.y >> 6));
}

Font::Font(const char* filePath, FT_Library library) :
    Font([&]() -> Font
    {
#if defined(_MSC_VER) && _MSC_VER >= 1400
        FILE* file = nullptr;
        fopen_s(&file, filePath, "rb");
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

        auto fileData = std::make_unique<std::byte[]>(fileDataBytes);
        fread(fileData.get(), 1, fileDataBytes, file);
        fclose(file);

        return Font(std::move(fileData), fileDataBytes, library);
    } ())
{
}

Font::Font(std::unique_ptr<std::byte[]> fileData, std::size_t fileDataBytes, FT_Library library) :
    m_fileData(std::move(fileData)),
    m_fileDataBytes(fileDataBytes),
    m_library(library)
{
}

Font::Font(Font&& rhs) noexcept :
    m_fileData(std::move(rhs.m_fileData)),
    m_fileDataBytes(rhs.m_fileDataBytes),
    m_library(rhs.m_library),
    m_fontFaces(std::move(rhs.m_fontFaces))
{
    rhs.m_fileDataBytes = 0;
    rhs.m_library = nullptr;
}

Font& Font::operator=(Font&& rhs) noexcept
{
    m_fileData = std::move(rhs.m_fileData);
    m_fileDataBytes = rhs.m_fileDataBytes;
    m_library = rhs.m_library;
    m_fontFaces = std::move(rhs.m_fontFaces);
    
    rhs.m_fileDataBytes = 0;
    rhs.m_library = nullptr;

    return *this;
}

const FontFace& Font::GetFace(FontSize fontSize) const
{
    auto iter = m_fontFaces.find(fontSize);
    if (iter != m_fontFaces.end())
    {
        return iter->second;
    }

    return m_fontFaces.insert(iter, {fontSize, FontFace(m_fileData.get(), m_fileDataBytes, m_library, fontSize)})->second;
}

const GlyphData& Font::GetGlyphData(UnicodeScalar ch, FontSize fontSize) const
{
    return this->GetFace(fontSize).GetGlyphData(ch);
}

I32Vector2 Font::GetKerning(UnicodeScalar lhs, UnicodeScalar rhs, FontSize fontSize) const
{
    return this->GetFace(fontSize).GetKerning(lhs, rhs);
}

FontFactory::FontFactory() :
    m_library(nullptr)
{
    FT_Error error = FT_Init_FreeType(&m_library) != 0;
    if (error)
    {
        Debug::Fail("Failed to invoke FT_Init_FreeType.", ConvertFTErrorToString(error));
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

std::shared_ptr<Font> FontFactory::CreateFont(const char* filePath) const
{
    return std::make_shared<Font>(filePath, m_library);
}

} /* namespace tgon */

#undef FT_ERRORDEF
#undef FT_ERROR_START_LIST
#undef FT_ERROR_END_LIST
#undef TGON_FT_CHECK_ERROR
