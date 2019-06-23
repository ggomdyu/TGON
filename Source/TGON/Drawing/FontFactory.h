/**
 * @file    FontFactory.h
 * @author  ggomdyu
 * @since   06/01/2019
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "String/StringHash.h"
#include "Math/Vector2.h"
#include "Math/Extent.h"
#include "Platform/Config.h"

namespace tgon
{

using FontSize = uint32_t;

struct GlyphData
{
/**@section Variable */
public:
    char32_t character;
    I32Extent2D size;
    I32Vector2 bearing;
    int32_t advance;
    std::unique_ptr<uint8_t[]> bitmap;
};

class TGON_API FontFace :
    private boost::noncopyable
{
/**@section Constructor */
public:
    FontFace(const uint8_t* fileData, std::size_t fileDataBytes, FT_Library library, FontSize fontSize);
    FontFace(FontFace&& rhs) noexcept;

/**@section Operator */
public:
    FontFace& operator=(FontFace&& rhs) noexcept;

/**@section Method */
public:
    const GlyphData& GetGlyphData(char32_t character) const;

/**@section Variable */
public:
    FT_Face m_fontFace;
    int32_t m_fontSize;
    mutable std::unordered_map<char32_t, GlyphData> m_glyphDatas;
};

class TGON_API Font :
    private boost::noncopyable
{
/**@section Constructor */
public:
    Font(const StringHash& fontPath, FT_Library library);
    Font(uint8_t* fileData, std::size_t fileDataBytes, FT_Library library);
    Font(Font&& rhs);

/**@section Method */
public:
    const FontFace& GetFace(FontSize fontSize) const;
    const GlyphData& GetGlyphData(char32_t character, FontSize fontSize) const;

/**@section Variable */
private:
    std::unique_ptr<uint8_t[]> m_fileData;
    std::size_t m_fileDataBytes;
    FT_Library m_library;
    mutable std::unordered_map<FontSize, FontFace> m_fontFaces;
};

class TGON_API FontFactory :
    private boost::noncopyable
{
/**@section Constructor */
public:
    FontFactory();

/**@section Destructor */
public:
    ~FontFactory();

/**@section Method */
public:
    std::shared_ptr<Font> GetFont(const StringHash& fontPath);

/**@section Variable */
private:
    FT_Library m_library;
    mutable std::unordered_map<StringHash, std::shared_ptr<Font>> m_fonts;
};

} /* namespace tgon */
