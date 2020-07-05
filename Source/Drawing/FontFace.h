#pragma once

#include <vector>
#include <cstddef>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Math/Vector2.h"
#include "Math/Extent.h"

typedef struct FT_LibraryRec_ FT_LibraryRec;
typedef struct FT_LibraryRec_* FT_Library;

namespace tg
{

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

class FontFace final
{
/**@section Constructor */
public:
    FontFace(FT_Face fontFace, int32_t fontSize) noexcept;
    FontFace(const FontFace& rhs) = delete;
    FontFace(FontFace&& rhs) noexcept;

/**@section Destructor */
public:
    ~FontFace();

/**@section Operator */
public:
    FontFace& operator=(const FontFace& rhs) = delete;
    FontFace& operator=(FontFace&& rhs) noexcept;

/**@section Method */
public:
    static std::shared_ptr<FontFace> Create(const std::shared_ptr<FT_LibraryRec>& library, const std::vector<std::byte>& fileData, int32_t fontSize);
    const GlyphData* GetGlyphData(char32_t ch) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs) const;

/**@section Variable */
private:
    FT_Face m_fontFace;
    int32_t m_fontSize;
    mutable std::unordered_map<char32_t, GlyphData> m_glyphDatas;
};

}
