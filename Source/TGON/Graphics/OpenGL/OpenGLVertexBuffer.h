/**
 * @file    OpenGLVertexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{
    
class OpenGLVertexBuffer :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLVertexBuffer(GLuint vertexBufferHandle) noexcept;
    OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept;
    
/**@section Operator */
protected:
    OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& rhs) noexcept;

/**@section Method */
public:
    GLuint GetVertexBufferHandle() const noexcept;

/**@section Variable */
protected:
    GLuint m_vertexBufferHandle;
};

using PlatformVertexBuffer = OpenGLVertexBuffer;

} /* namespace tgon */
#endif
