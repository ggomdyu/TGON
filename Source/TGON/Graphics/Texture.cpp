#include "PrecompiledHeader.h"

#include "String/Hash.h"

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

}
