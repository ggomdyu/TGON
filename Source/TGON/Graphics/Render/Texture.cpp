#include "PrecompiledHeader.pch"

#include "Texture.h"

namespace tgon
{
namespace graphics
{

Texture2D::Texture2D(const std::string& filePath) :
    m_filePath(filePath)
{
}

Texture2D::Texture2D(std::string&& filePath) :
    m_filePath(filePath)
{
}

const std::string& Texture2D::GetFilePath() const noexcept
{
    return m_filePath;
}

uint8_t* Texture2D::GetBits() noexcept
{
    return m_bits;
}

uint32_t Texture2D::GetWidth() const noexcept
{
    return m_width;
}

uint32_t Texture2D::GetHeight() const noexcept
{
    return m_height;
}

} /* namespace graphics */
} /* namespace tgon */