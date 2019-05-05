/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{
    
class TGON_API Texture final :
    private PlatformTexture
{
/**@section Constructor */
public:
    explicit Texture(const std::string& filePath, const TextureProperty& textureProperty = {});
   
/**@section Method */
public:
    PlatformTexture* GetPlatformDependency() noexcept;
    const PlatformTexture* GetPlatformDependency() const noexcept;
    
    using PlatformTexture::Use;
    using PlatformTexture::SetFilterMode;
    using PlatformTexture::SetWrapMode;
    using PlatformTexture::GetFilterMode;
    using PlatformTexture::GetWrapMode;
    using PlatformTexture::GetWidth;
    using PlatformTexture::GetHeight;
    using PlatformTexture::GetSize;
    using PlatformTexture::GetChannels;
    using PlatformTexture::GetPixelFormat;
    using PlatformTexture::GetFilePath;
};
    
} /* namespace tgon */
