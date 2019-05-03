#include "PrecompiledHeader.h"

#include "Core/Hash/Hash.h"

#include "Texture.h"

namespace tgon
{

Texture::Texture(const std::string& filePath, const TextureProperty& textureProperty) :
    PlatformTexture(filePath, textureProperty)
{
}
    
PlatformTexture* Texture::GetPlatformDependency() noexcept
{
    return this;
}

const PlatformTexture* Texture::GetPlatformDependency() const noexcept
{
    return this;
}

} /* namespace tgon */
