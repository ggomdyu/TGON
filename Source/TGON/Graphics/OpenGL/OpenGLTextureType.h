/**
 * @file    OpenGLTextureType.h
 * @author  ggomdyu
 * @since   03/22/2018
 */

#pragma once
#include <GL/glew.h>

namespace tgon
{

enum class TextureFilterMode : GLint
{
    Point = GL_NEAREST,
    Bilinear = GL_LINEAR,
};

enum class TextureWrapMode : GLint
{
    Repeat = GL_REPEAT,
    Clamp = GL_CLAMP,
    Mirror = GL_MIRRORED_REPEAT,
};

} /* namespace tgon */
