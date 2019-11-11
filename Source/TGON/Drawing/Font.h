/**
 * @file    Font.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "FontFace.h"

namespace tgon
{

class TGON_API Font final :
    private NonCopyable
{
/**@section Constructor */
public:
    Font(const char* filePath, FT_Library library);
    Font(const std::vector<std::byte>& fileData, FT_Library library);
    Font(std::vector<std::byte>&& fileData, FT_Library library);
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
    const GlyphData& GetGlyphData(char32_t ch, FontSize fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, FontSize fontSize) const;

/**@section Variable */
private:
    std::vector<std::byte> m_fileData;
    FT_Library m_library;
    mutable std::unordered_map<FontSize, FontFace> m_fontFaces;
};

} /* namespace tgon */
