#pragma once

#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"

namespace tg
{
    
class OpenGLVertexBuffer :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit OpenGLVertexBuffer(GLuint vertexBufferHandle) noexcept;
    OpenGLVertexBuffer(const OpenGLVertexBuffer& rhs) = delete;
    OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~OpenGLVertexBuffer() = default;
    
/**@section Operator */
public:
    OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer& rhs) = delete;
    OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& rhs) noexcept;

/**@section Method */
public:
    [[nodiscard]] static GLuint CreateVertexBufferHandle();
    [[nodiscard]] GLuint GetVertexBufferHandle() const noexcept;

/**@section Variable */
protected:
    GLuint m_vertexBufferHandle;
};

using PlatformVertexBuffer = OpenGLVertexBuffer;

}
#endif
