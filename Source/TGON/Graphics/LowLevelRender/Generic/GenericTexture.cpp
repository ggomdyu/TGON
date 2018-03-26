
#include "PrecompiledHeader.pch"

#include "GenericTexture.h"

namespace tgon
{

GenericTexture::GenericTexture(const std::string& imagePath, const TextureCreateDesc& textureCreateDesc) :
    Bitmap(imagePath),
    m_isUseMipmap(textureCreateDesc.isUseMipmap)
{
}

bool GenericTexture::IsUseMipmap() const noexcept
{
    return m_isUseMipmap;
}
    
} /* namespace tgon */