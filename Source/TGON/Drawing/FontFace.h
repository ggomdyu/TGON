/**
 * @file    FontFace.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include <vector>
#include <memory>
#include <cstddef>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Core/NonCopyable.h"
#include "Math/Vector2.h"
#include "Math/Extent.h"
#include "Platform/Config.h"

namespace tgon
{

using FontSize = int32_t;

struct GlyphMetrics final
{
    I32Extent2D size;
    I32Vector2 bearing;
    I32Vector2 advance;
};

struct GlyphData final
{
    char32_t ch;
    GlyphMetrics metrics;
    std::unique_ptr<std::byte[]> bitmap;
};

class TGON_API FontFace final :
    private NonCopyable
{
/**@section Constructor */
public:
    FontFace(const std::vector<std::byte>& fileData, FT_Library library, FontSize fontSize);
    FontFace(FontFace&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~FontFace();

/**@section Operator */
public:
    FontFace& operator=(FontFace&& rhs) noexcept;

/**@section Method */
public:
    const GlyphData& GetGlyphData(char32_t ch) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs) const;

private:
    void Destroy();

/**@section Variable */
public:
    FontSize m_fontSize;
    FT_Face m_fontFace;
    mutable std::unordered_map<char32_t, GlyphData> m_glyphDatas;
};

} /* namespace tgon */
