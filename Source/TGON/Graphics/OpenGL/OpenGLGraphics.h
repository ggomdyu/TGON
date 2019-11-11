/**
 * @file    OpenGLGraphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"

#include "OpenGLContext.h"

namespace tgon
{
    
class TGON_API OpenGLGraphics :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLGraphics(OpenGLContext&& context) noexcept;
    
/**@section Method */
public:
    OpenGLContext& GetContext() noexcept;
    const OpenGLContext& GetContext() const noexcept;
    GLuint GetVertexArrayHandle() const noexcept;

/**@section Variable */
protected:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle;
};

using PlatformGraphics = OpenGLGraphics;

} /* namespace tgon */
#endif
