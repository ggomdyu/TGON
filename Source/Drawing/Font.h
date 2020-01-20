/**
 * @file    Font.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include "FontFace.h"

namespace tgon
{

class Font final :
    private NonCopyable
{
/**@section Constructor */
public:
    template <typename _ContainerType>
    Font(FT_Library library, _ContainerType&& fileData);
    Font(Font&& rhs) noexcept;

/**@section Operator */
public:
    Font& operator=(Font&& rhs) noexcept;

/**@section Method */
public:
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetCharSize(char32_t ch, int32_t fontSize);
    std::shared_ptr<FontFace> GetFace(int32_t fontSize);
    std::shared_ptr<const FontFace> GetFace(int32_t fontSize) const;

/**@section Variable */
private:
    FT_Library m_library;
    std::vector<std::byte> m_fileData;
    mutable std::unordered_map<int32_t, std::shared_ptr<FontFace>> m_fontFaces;
};

template <typename _ContainerType>
inline Font::Font(FT_Library library, _ContainerType&& fileData) :
    m_library(library),
    m_fileData(std::forward<_ContainerType>(fileData))
{
}

} /* namespace tgon */
