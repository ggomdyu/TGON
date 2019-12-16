#include "PrecompiledHeader.h"

#include "IO/File.h"

#include "Font.h"

namespace tgon
{

extern const char* ConvertFTErrorToString(FT_Error error);

Font::Font(FT_Library library) noexcept :
    m_library(library)
{
}

Font::Font(const char* filePath, FT_Library library) :
    Font(library)
{
    this->Initialize(filePath);
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

bool Font::Initialize(const char* filePath)
{
    auto fileData = File::ReadAllBytes(filePath, ReturnVectorTag{});
    if (fileData.has_value() == false)
    {
        return false;
    }

    this->Initialize(*fileData);
    return true;
}

void Font::Initialize(std::vector<std::byte>&& fileData)
{
    m_fontFaces.clear();
    m_fileData = std::move(fileData);
}

void Font::Initialize(const std::vector<std::byte>& fileData)
{
    m_fontFaces.clear();
    m_fileData = fileData;
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

I32Extent2D Font::GetCharSize(char32_t ch, int32_t fontSize)
{
    return this->GetFace(fontSize).GetGlyphData(ch).metrics.size;
}

} /* namespace tgon */
