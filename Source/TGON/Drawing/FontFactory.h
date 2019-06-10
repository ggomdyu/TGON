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
    //constexpr const size_t GetHashCode() noexcept;

    char32_t character;
    I32Extent2D size;
    I32Vector2 bearing;
    int32_t advance;
    std::unique_ptr<uint8_t[]> bitmap;
};

class TGON_API Font :
    private boost::noncopyable
{
/**@section Constructor */
public:
    Font(const StringHash& fontPath, FT_Library fontLibrary);

/**@section Method */
public:
    const GlyphData& GetGlyphData(char32_t character, int32_t size) const;

/**@section Variable */
private:
    StringHash m_fontPath;
    FT_Library m_fontLibrary;
    FT_Face m_fontFace;
    mutable std::unordered_map<char32_t, std::unordered_map<int32_t, GlyphData>> m_glyphDataCaches;
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
    FT_Library m_fontLibrary;
    mutable std::unordered_map<StringHash, std::shared_ptr<Font>> m_fonts;
};

} /* namespace tgon */
