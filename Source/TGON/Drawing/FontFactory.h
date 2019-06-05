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

class TGON_API GlyphData :
    private boost::noncopyable
{
/**@section Constructor */
public:
    GlyphData(char32_t ch, FT_Face fontFace) noexcept;

/**@section Destructor */
public:
    ~GlyphData();

/**@section Method */
public:
    I32Extent2D GetSize() const noexcept;
    I32Vector2 GetBearing() const noexcept;
    int32_t GetAdvance() const noexcept;
    uint8_t* GetImageData() noexcept;
    const uint8_t* GetImageData() const noexcept;
    char32_t GetCharacter() const noexcept;
    
/**@section Variable */
private:
    char32_t m_ch;
    FT_Face m_fontFace;
};

class TGON_API Font
{
public:
    StringHash m_font;
    int32_t m_height;
};

class FontBakery
{
public:
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
    FT_Face GetGlyphData(const StringHash& fontPath, char32_t ch);
    FT_Face LoadFontFace(const StringHash& fontPath, int32_t height);

private:

/**@section Variable */
private:
    FT_Library m_fontLibrary;
    std::unordered_map<StringHash, FT_Face> m_fontFaces;
};

} /* namespace tgon */
