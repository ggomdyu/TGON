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
    explicit Font(FT_Library library) noexcept;
    Font(const char* filePath, FT_Library library);
    Font(const std::vector<std::byte>& fileData, FT_Library library);
    Font(std::vector<std::byte>&& fileData, FT_Library library);
    Font(Font&& rhs) noexcept;

/**@section Operator */
public:
    Font& operator=(Font&& rhs) noexcept;

/**@section Method */
public:
    bool Initialize(const char* filePath);
    void Initialize(std::vector<std::byte>&& fileData);
    void Initialize(const std::vector<std::byte>& fileData);
    const FontFace& GetFace(int32_t fontSize) const;
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetCharSize(char32_t ch, int32_t fontSize);

/**@section Variable */
private:
    std::vector<std::byte> m_fileData;
    FT_Library m_library = nullptr;
    mutable std::unordered_map<int32_t, FontFace> m_fontFaces;
};

} /* namespace tgon */
