/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"

namespace tgon
{

class OpenGLTexture :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLTexture() noexcept;
    OpenGLTexture(OpenGLTexture&& rhs) noexcept;
    
/**@section Destructor */
protected:
    ~OpenGLTexture();

/**@section Operator */
protected:
    OpenGLTexture& operator=(OpenGLTexture&& rhs) noexcept;

/**@section Method */
protected:
    void Use();
    void Unuse();
    void CreateMipmap() const;
    GLuint GetTextureHandle() const noexcept;
    void Destroy();

private:
    void UpdateTexParameters();

/**@section Variable */
protected:
    GLuint m_textureHandle;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
#endif
