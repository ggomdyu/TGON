/**
 * @filename    OpenGLTextureUtility.h
 * @author      ggomdyu
 * @since       03/22/2018
 */

#pragma once
#include <GL/glew.h>

#include "Core/Utility/Algorithm.h"

#include "../Generic/GenericTextureType.h"

namespace tgon
{

constexpr GLint ConvertTextureFilterModeToNative(TextureFilterMode filterMode) noexcept
{
    constexpr GLint nativeTextureFilterModeTable[] =
    {
        GL_NEAREST,
        GL_LINEAR,
    };

    return nativeTextureFilterModeTable[ToUnderlying(filterMode)];
}

constexpr TextureFilterMode ConvertNativeToTextureFilterMode(GLint filterMode)
{
    if (filterMode == GL_LINEAR)
    {
        return TextureFilterMode::Bilinear;
    }
    else if (filterMode == GL_NEAREST)
    {
        return TextureFilterMode::Point;
    }
    else
    {
        return TextureFilterMode(0);
    }
};

constexpr GLint ConvertTextureWrapModeToNative(TextureWrapMode wrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModeTable[] =
    {
        GL_REPEAT,
        GL_CLAMP,
        GL_MIRRORED_REPEAT,
    };

    return nativeTextureWrapModeTable[ToUnderlying(wrapMode)];
}

constexpr TextureWrapMode ConvertNativeToTextureWrapMode(GLint wrapMode) noexcept
{
    switch (wrapMode)
    {
    case GL_REPEAT:
        return TextureWrapMode::Repeat;

    case GL_CLAMP:
        return TextureWrapMode::Clamp;

    case GL_MIRRORED_REPEAT:
        return TextureWrapMode::Mirror;

    default:
        return TextureWrapMode(0);
    }
}

} /* namespace tgon */