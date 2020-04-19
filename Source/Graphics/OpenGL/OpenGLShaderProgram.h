#pragma once

#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"

namespace tg
{

class OpenGLShaderProgram :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
    OpenGLShaderProgram(OpenGLShaderProgram&& rhs) noexcept;

/**@section Destructor */
protected:
    ~OpenGLShaderProgram();
    
/**@section Operator */
protected:
    OpenGLShaderProgram& operator=(OpenGLShaderProgram&& rhs) noexcept;
    
/**@section Method */
public:
    GLuint GetProgramId() const noexcept;
    
/**@section Variable */
protected:
    GLuint m_programId;
    inline static OpenGLShaderProgram* g_lastUsedShaderProgram;
};
    
using PlatformShaderProgram = OpenGLShaderProgram;
    
}
#endif
