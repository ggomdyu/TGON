/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include "Platform/Config.h"

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
    using PlatformTexture::PlatformTexture;
   
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
    using PlatformTexture::GetPixelFormat;
};
    
} /* namespace tgon */
