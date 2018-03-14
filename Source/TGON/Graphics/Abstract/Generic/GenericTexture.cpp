
#include "PrecompiledHeader.pch"

#include "GenericTexture.h"

namespace tgon
{
namespace graphics
{

GenericTexture::GenericTexture(const std::string& imagePath, const TextureCreateDesc& textureCreateDesc) :
    core::Bitmap(imagePath),
    m_isUseMipmap(textureCreateDesc.isUseMipmap)
{
}

bool GenericTexture::IsUseMipmap() const noexcept
{
    return m_isUseMipmap;
}
    
} /* namespace graphics */
} /* namespace tgon */
