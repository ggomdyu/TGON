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
    
class OpenGLGraphics :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLGraphics(const std::shared_ptr<Window>& displayWindow, const VideoMode& videoMode);
    OpenGLGraphics(OpenGLGraphics&& rhs) noexcept;

protected:
    ~OpenGLGraphics();

/**@section Method */
public:
    OpenGLContext& GetContext() noexcept;
    const OpenGLContext& GetContext() const noexcept;

protected:
    GLuint GetVertexArrayHandle() const noexcept;

/**@section Variable */
protected:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle = 0;
};

using PlatformGraphics = OpenGLGraphics;

} /* namespace tgon */
#endif
