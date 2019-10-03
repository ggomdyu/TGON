/**
 * @file    FontFactory.h
 * @author  ggomdyu
 * @since   06/01/2019
 */

#pragma once
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Core/NonCopyable.h"
#include "String/StringHash.h"
#include "String/UnicodeScalar.h"
#include "Math/Vector2.h"
#include "Math/Extent.h"
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   undef CreateFont
#endif

namespace tgon
{

using FontSize = uint32_t;

struct GlyphMetrics final
{
    I32Extent2D size;
    I32Vector2 bearing;
    I32Vector2 advance;
};

struct GlyphData final
{
    UnicodeScalar ch;
    GlyphMetrics metrics;
    std::unique_ptr<std::byte[]> bitmap;
};

class TGON_API FontFace final :
    private NonCopyable
{
/**@section Constructor */
public:
    FontFace(const std::byte* fileData, std::size_t fileDataBytes, FT_Library library, FontSize fontSize);
    FontFace(FontFace&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~FontFace() = default;

/**@section Operator */
public:
    FontFace& operator=(FontFace&& rhs) noexcept;

/**@section Method */
public:
    const GlyphData& GetGlyphData(UnicodeScalar ch) const;
    I32Vector2 GetKerning(UnicodeScalar lhs, UnicodeScalar rhs) const;

/**@section Variable */
public:
    int32_t m_fontSize;
    FT_Face m_fontFace;
    mutable std::unordered_map<UnicodeScalar, GlyphData> m_glyphDatas;
};

class TGON_API Font final :
    private NonCopyable
{
/**@section Constructor */
public:
    Font(const char* filePath, FT_Library library);
    Font(std::unique_ptr<std::byte[]> fileData, std::size_t fileDataBytes, FT_Library library);
    Font(Font&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~Font() = default;
    
/**@section Operator */
public:
    Font& operator=(Font&& rhs) noexcept;

/**@section Method */
public:
    const FontFace& GetFace(FontSize fontSize) const;
    const GlyphData& GetGlyphData(UnicodeScalar ch, FontSize fontSize) const;
    I32Vector2 GetKerning(UnicodeScalar lhs, UnicodeScalar rhs, FontSize fontSize) const;

/**@section Variable */
private:
    std::unique_ptr<std::byte[]> m_fileData;
    std::size_t m_fileDataBytes;
    FT_Library m_library;
    mutable std::unordered_map<FontSize, FontFace> m_fontFaces;
};

class TGON_API FontFactory :
    private NonCopyable
{
/**@section Constructor */
public:
    FontFactory();

/**@section Destructor */
public:
    ~FontFactory();

/**@section Method */
public:
    std::shared_ptr<Font> CreateFont(const char* filePath) const;

/**@section Variable */
private:
    FT_Library m_library;
};

} /* namespace tgon */
