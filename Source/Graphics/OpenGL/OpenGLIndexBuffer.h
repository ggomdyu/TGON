#pragma once

#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"

namespace tg
{

class OpenGLIndexBuffer :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLIndexBuffer(GLuint indexBufferHandle) noexcept;
    OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) noexcept;

/**@section Operator */
protected:
    OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&& rhs) noexcept;
    
/**@section Method */
public:
    GLuint GetIndexBufferHandle() const noexcept;

/**@section Variable */
protected:
    GLuint m_indexBufferHandle;
};
    
using PlatformIndexBuffer = OpenGLIndexBuffer;

}
#endif
