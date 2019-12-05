/**
 * @file    Font.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include "FontFace.h"

namespace tgon
{

class Font :
    private NonCopyable
{
/**@section Constructor */
public:
    Font(const char* filePath, FT_Library library);
    Font(const std::vector<std::byte>& fileData, FT_Library library);
    Font(std::vector<std::byte>&& fileData, FT_Library library);
    Font(Font&& rhs) noexcept;

/**@section Operator */
public:
    Font& operator=(Font&& rhs) noexcept;

/**@section Method */
public:
    const FontFace& GetFace(int32_t fontSize) const;
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetTextSize(int32_t fontSize);
    I32Extent2D GetTextSize(int32_t fontSize, const I32Extent2D& rect) const;

/**@section Variable */
private:
    std::vector<std::byte> m_fileData;
    FT_Library m_library;
    mutable std::unordered_map<int32_t, FontFace> m_fontFaces;
};

} /* namespace tgon */
