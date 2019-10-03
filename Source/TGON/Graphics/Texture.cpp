#include "PrecompiledHeader.h"

#include "Texture.h"

namespace tgon
{

PlatformTexture* Texture::GetPlatformDependency() noexcept
{
    return this;
}

const PlatformTexture* Texture::GetPlatformDependency() const noexcept
{
    return this;
}

} /* namespace tgon */
