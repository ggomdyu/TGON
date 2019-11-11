#include "PrecompiledHeader.h"

#include <stdexcept>

#include "Diagnostics/Debug.h"
#include "IO/File.h"

#include "FontFactory.h"

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  {e, s},
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       {0, 0}};

namespace tgon
{

const char* ConvertFTErrorToString(FT_Error error)
{
    static constexpr const struct
    {
        int errorCode;
        const char* errorMessage;
    } ftErrors[] =
    #include FT_ERRORS_H
    
    return ftErrors[error].errorMessage;
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

FontFace::FontFace(const std::vector<std::byte>& fileData, FT_Library library, FontSize fontSize) :
    m_fontSize(fontSize),
    m_fontFace([&]() -> FT_Face
    {
        FT_Face face = nullptr;
        FT_Error error = FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(fileData.data()), fileData.size(), 0, &face);
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

FontFace::~FontFace()
{
    this->Destroy();
}

FontFace& FontFace::operator=(FontFace&& rhs) noexcept
{
    this->Destroy();

    m_fontSize = rhs.m_fontSize;
    m_fontFace = rhs.m_fontFace;
    m_glyphDatas = std::move(rhs.m_glyphDatas);

    rhs.m_fontSize = 0;
    rhs.m_fontFace = nullptr;

    return *this;
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

Font::Font(const char* filePath, FT_Library library) :
    Font(File::ReadAllBytes(filePath).value_or(std::vector<std::byte>()), library)
{
}

Font::Font(const std::vector<std::byte>& fileData, FT_Library library) :
    m_fileData(fileData),
    m_library(library)
{
}

Font::Font(std::vector<std::byte>&& fileData, FT_Library library) :
    m_fileData(std::move(fileData)),
    m_library(library)
{
}

Font::Font(Font&& rhs) noexcept :
    m_fileData(std::move(rhs.m_fileData)),
    m_library(rhs.m_library),
    m_fontFaces(std::move(rhs.m_fontFaces))
{
    rhs.m_library = nullptr;
}

Font& Font::operator=(Font&& rhs) noexcept
{
    m_fileData = std::move(rhs.m_fileData);
    m_library = rhs.m_library;
    m_fontFaces = std::move(rhs.m_fontFaces);
    
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

    return m_fontFaces.insert(iter, {fontSize, FontFace(m_fileData, m_library, fontSize)})->second;
}

const GlyphData& Font::GetGlyphData(char32_t ch, FontSize fontSize) const
{
    return this->GetFace(fontSize).GetGlyphData(ch);
}

I32Vector2 Font::GetKerning(char32_t lhs, char32_t rhs, FontSize fontSize) const
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

FT_Library FontFactory::GetFTLibrary() noexcept
{
    return m_library;
}

const FT_Library FontFactory::GetFTLibrary() const noexcept
{
    return m_library;
}

} /* namespace tgon */

#undef FT_ERRORDEF
#undef FT_ERROR_START_LIST
#undef FT_ERROR_END_LIST
