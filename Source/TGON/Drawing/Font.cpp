#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"
#include "IO/File.h"

#include "Font.h"

namespace tgon
{

extern const char* ConvertFTErrorToString(FT_Error error);

Font::Font(const char* filePath, FT_Library library) :
    Font(File::ReadAllBytes(filePath).value_or(std::vector<std::byte>()), library)
{
}

Font::Font(const std::vector<std::byte>& fileData, FT_Library library) :
    m_fileData(fileData),
    m_library(library)
{
}

Font::Font(std::vector<std::byte>&& fileData, FT_Library library) :
    m_fileData(std::move(fileData)),
    m_library(library)
{
}

Font::Font(Font&& rhs) noexcept :
    m_fileData(std::move(rhs.m_fileData)),
    m_library(rhs.m_library),
    m_fontFaces(std::move(rhs.m_fontFaces))
{
    rhs.m_library = nullptr;
}

Font& Font::operator=(Font&& rhs) noexcept
{
    m_fileData = std::move(rhs.m_fileData);
    m_library = rhs.m_library;
    m_fontFaces = std::move(rhs.m_fontFaces);
    
    rhs.m_library = nullptr;

    return *this;
}

const FontFace& Font::GetFace(int32_t fontSize) const
{
    auto iter = m_fontFaces.find(fontSize);
    if (iter != m_fontFaces.end())
    {
        return iter->second;
    }

    return m_fontFaces.emplace_hint(iter, fontSize, FontFace(m_fileData, m_library, fontSize))->second;
}

const GlyphData& Font::GetGlyphData(char32_t ch, int32_t fontSize) const
{
    return this->GetFace(fontSize).GetGlyphData(ch);
}

I32Vector2 Font::GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const
{
    return this->GetFace(fontSize).GetKerning(lhs, rhs);
}

I32Extent2D Font::GetTextSize(int32_t fontSize)
{
    // TODO: Impl
    return {};
}

I32Extent2D Font::GetTextSize(int32_t fontSize, const I32Extent2D& rect) const
{
    // TODO: Impl
    return {};
}

} /* namespace tgon */
