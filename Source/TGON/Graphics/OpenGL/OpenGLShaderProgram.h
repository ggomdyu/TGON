/**
 * @file    OpenGLShaderProgram.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <string>
#include <array>
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class TGON_API OpenGLShaderProgram :
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
protected:
    GLuint CompileShader(GLenum shaderType, const char* shaderCode) const;
    bool IsShaderCompileSucceed(GLuint shaderId) const;
    std::string GetShaderInfoLog(GLuint shaderId) const;
    
/**@section Variable */
protected:
    GLuint m_programId;
    std::array<int32_t, 8> m_uniformLocationCache;
};
    
using PlatformShaderProgram = OpenGLShaderProgram;
    
} /* namespace tgon */
