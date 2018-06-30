/**
 * @file    TextureType.h
 * @author  ggomdyu
 * @since   06/30/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTextureType.h"
#endif

namespace tgon
{
 
struct TextureProperty
{
    TextureFilterMode filterMode = TextureFilterMode::Bilinear;
    TextureWrapMode wrapMode = TextureWrapMode::Repeat;
    bool isUseMipmap = true;
};
    
} /* namespace tgon */
