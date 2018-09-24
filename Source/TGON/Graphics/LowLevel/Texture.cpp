#include "PrecompiledHeader.h"

#include "Core/Hash/Hash.h"

#include "Texture.h"

namespace tgon
{

Texture::Texture(const std::string& filePath, const TextureProperty& textureProperty) :
    IResource(X65599Hash(filePath.c_str())),
    PlatformTexture(filePath, textureProperty)
{
}

} /* namespace tgon */