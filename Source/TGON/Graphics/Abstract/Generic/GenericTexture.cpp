#include "PrecompiledHeader.pch"

#include "GenericTexture.h"

namespace tgon
{
namespace graphics
{

TextureFilterMode GenericTexture::GetFilterMode() const noexcept
{
    return m_filterMode;
}

TextureAddressMode GenericTexture::GetAddressMode() const noexcept
{
    return m_addressMode;
}
    
} /* namespace graphics */
} /* namespace tgon */
