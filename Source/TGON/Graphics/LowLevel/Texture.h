/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Object/IResource.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{
    
class TGON_API Texture final :
    public IResource,
    private PlatformTexture
{
/**@section Public constructor */
public:
    explicit Texture(const std::string& filePath, const TextureProperty& textureProperty = {});
   
/**@section Public method */
public:
    using PlatformTexture::Use;
    using PlatformTexture::SetFilterMode;
    using PlatformTexture::SetWrapMode;
    using PlatformTexture::GetFilterMode;
    using PlatformTexture::GetWrapMode;
    using PlatformTexture::GetWidth;
    using PlatformTexture::GetHeight;
    using PlatformTexture::GetChannels;
    using PlatformTexture::GetPixelFormat;
};
    
} /* namespace tgon */
