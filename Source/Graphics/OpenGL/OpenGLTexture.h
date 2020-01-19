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
public:
    OpenGLTexture();
    OpenGLTexture(void* nativeTexture) noexcept;
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
    void UpdateTexParameters();
    void CreateMipmap() const;
    void Destroy();

/**@section Variable */
protected:
    GLuint m_textureHandle;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
#endif
