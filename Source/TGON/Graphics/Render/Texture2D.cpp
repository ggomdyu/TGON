#include "PrecompiledHeader.pch"
#include "Texture2D.h"

namespace tgon
{
namespace render
{

Texture2D::Texture2D(const char* imageFilePath)
{

}

uint32_t Texture2D::GetWidth() const noexcept
{
    return m_width;
}

uint32_t Texture2D::GetHeight() const noexcept
{
    return m_height;
}

} /* namespace render */
} /* namespace tgon */
