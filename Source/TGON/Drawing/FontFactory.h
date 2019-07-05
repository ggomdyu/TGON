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

#if TGON_PLATFORM_WINDOWS
#   undef CreateFont
#endif

namespace tgon
{

using FontSize = uint32_t;

struct GlyphMetrics
{
    I32Extent2D size;
    I32Vector2 bearing;
    int32_t advance;
};

struct GlyphData
{
/**@section Variable */
public:
    char32_t character;
    I32Extent2D size;
    I32Vector2 bearing;
    I32Vector2 advance;
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
    const I32Vector2 GetKerning(char32_t lhs, char32_t rhs) const;

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
    Font(const StringHash& filePath, FT_Library library);
    Font(uint8_t* fileData, std::size_t fileDataBytes, FT_Library library);
    Font(Font&& rhs);

/**@section Method */
public:
    const FontFace& GetFace(FontSize fontSize) const;
    const GlyphData& GetGlyphData(char32_t character, FontSize fontSize) const;
    const I32Vector2 GetKerning(char32_t lhs, char32_t rhs, FontSize fontSize) const;

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
    std::shared_ptr<Font> CreateFont(const StringHash& filePath) const;

/**@section Variable */
private:
    FT_Library m_library;
};

} /* namespace tgon */
