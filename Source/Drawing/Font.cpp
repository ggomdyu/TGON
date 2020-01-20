#include "PrecompiledHeader.h"

#include "IO/File.h"

#include "Font.h"

namespace tgon
{

extern const char* ConvertFTErrorToString(FT_Error error);

Font::Font(Font&& rhs) noexcept :
    m_library(rhs.m_library),
    m_fileData(std::move(rhs.m_fileData)),
    m_fontFaces(std::move(rhs.m_fontFaces))
{
    rhs.m_library = nullptr;
}

Font& Font::operator=(Font&& rhs) noexcept
{
    std::swap(m_fileData, rhs.m_fileData);
    std::swap(m_library, rhs.m_library);
    std::swap(m_fontFaces, rhs.m_fontFaces);
    
    return *this;
}

std::shared_ptr<FontFace> Font::GetFace(int32_t fontSize)
{
    auto iter = m_fontFaces.find(fontSize);
    if (iter != m_fontFaces.end())
    {
        return iter->second;
    }

    return m_fontFaces.emplace_hint(iter, fontSize, FontFace::Create(m_library, m_fileData, fontSize))->second;
}

std::shared_ptr<const FontFace> Font::GetFace(int32_t fontSize) const
{
    return const_cast<Font*>(this)->GetFace(fontSize);
}

const GlyphData& Font::GetGlyphData(char32_t ch, int32_t fontSize) const
{
    return this->GetFace(fontSize)->GetGlyphData(ch);
}

I32Vector2 Font::GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const
{
    return this->GetFace(fontSize)->GetKerning(lhs, rhs);
}

I32Extent2D Font::GetCharSize(char32_t ch, int32_t fontSize)
{
    return this->GetFace(fontSize)->GetGlyphData(ch).metrics.size;
}

} /* namespace tgon */
