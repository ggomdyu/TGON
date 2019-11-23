/**
 * @file    OpenGLShaderProgram.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class OpenGLShaderProgram :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLShaderProgram(GLuint programId) noexcept;
    OpenGLShaderProgram(OpenGLShaderProgram&& rhs) noexcept;

/**@section Operator */
protected:
    OpenGLShaderProgram& operator=(OpenGLShaderProgram&& rhs) noexcept;
    
/**@section Method */
public:
    GLuint GetProgramId() const noexcept;
    
/**@section Variable */
protected:
    GLuint m_programId;
};
    
using PlatformShaderProgram = OpenGLShaderProgram;
    
} /* namespace tgon */
#endif
