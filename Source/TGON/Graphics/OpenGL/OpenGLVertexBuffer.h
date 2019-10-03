/**
 * @file    OpenGLVertexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{
    
class TGON_API OpenGLVertexBuffer :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLVertexBuffer(GLuint vertexBufferHandle) noexcept;
    OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept;
    
/**@section Operator */
protected:
    OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& rhs);

/**@section Method */
protected:
    void Destroy();

/**@section Variable */
protected:
    GLuint m_vertexBufferHandle;
};

using PlatformVertexBuffer = OpenGLVertexBuffer;

} /* namespace tgon */
