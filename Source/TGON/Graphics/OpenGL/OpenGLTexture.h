/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class TGON_API OpenGLTexture :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLTexture(GLuint textureHandle) noexcept;
    OpenGLTexture(OpenGLTexture&& rhs) noexcept;
    
/**@section Operator */
public:
    OpenGLTexture& operator=(OpenGLTexture&& rhs) noexcept;

/**@section Method */
protected:
    GLuint GetTextureHandle() const noexcept;
    void CreateMipmap() const;

/**@section Variable */
protected:
    GLuint m_textureHandle;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
#endif
