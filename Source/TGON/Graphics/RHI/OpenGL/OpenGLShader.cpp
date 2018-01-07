#include "PrecompiledHeader.pch"

#include "OpenGLShader.h"

#include "Core/Debug/Log.h"

#include <cassert>

#if _DEBUG
#   define V(expression)\
    {\
        expression;\
        GLenum errorCode = glGetError();\
        if (errorCode != GL_NO_ERROR)\
        {\
            core::Log("Failed to invoke OpenGL function. (Code: %d, File:%s, Function:%s, Line:%d)", errorCode, __FILE__, __FUNCTION__, __LINE__);\
        }\
    }
#else
#   define V(expression) expression;
#endif

namespace tgon
{
namespace graphics
{

bool OpenGLShader::Initialize(const char* vertexShaderCodeStr, const char* fragmentShaderCodeStr)
{
    assert(vertexShaderCodeStr != nullptr);
    assert(fragmentShaderCodeStr != nullptr);

    GLuint vertexShader = this->CompileShader(GL_VERTEX_SHADER, vertexShaderCodeStr);
    if (vertexShader == 0)
    {
        return false;
    }

    GLuint fragmentShader = this->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCodeStr);
    if (fragmentShader == 0)
    {
        return false;
    }
    
    this->Link(vertexShader, fragmentShader);

    return true;
}

void OpenGLShader::BeginScene()
{
    glUseProgram(m_program);
}

void OpenGLShader::EndScene()
{
    glUseProgram(0);
}

void OpenGLShader::BindAttributeLocation(const char* name, std::size_t index)
{
    glBindAttribLocation(m_program, index, name);
}

int OpenGLShader::GetUniformLocation(const char* name) const
{
    return glGetUniformLocation(m_program, name);
}

void OpenGLShader::SetParameter1f(const char* name, GLfloat f)
{
    this->SetParameter1f(this->GetUniformLocation(name), f);
}

void OpenGLShader::SetParameter2f(const char* name, GLfloat f1, GLfloat f2)
{
    this->SetParameter2f(this->GetUniformLocation(name), f1, f2);
}

void OpenGLShader::SetParameter3f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3)
{
    this->SetParameter3f(this->GetUniformLocation(name), f1, f2, f3);
}

void OpenGLShader::SetParameter4f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    this->SetParameter4f(this->GetUniformLocation(name), f1, f2, f3, f4);
}

void OpenGLShader::SetParameter1f(int32_t location, GLfloat f)
{
    glUniform1f(location, f);
}

void OpenGLShader::SetParameter2f(int32_t location, GLfloat f1, GLfloat f2)
{
    glUniform2f(location, f1, f2);
}

void OpenGLShader::SetParameter3f(int32_t location, GLfloat f1, GLfloat f2, GLfloat f3)
{
    glUniform3f(location, f1, f2, f3);
}

void OpenGLShader::SetParameter4f(int32_t location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    glUniform4f(location, f1, f2, f3, f4);
}

void OpenGLShader::SetParameterSampler(int32_t location, int textureSlot, std::size_t sampler)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);

    glBindTexture(GL_TEXTURE_2D, sampler);
    glUniform1i(location, sampler);
}

bool OpenGLShader::Link(GLuint vertexShader, GLuint fragmentShader)
{
    // Creates an empty program object.
    m_program = glCreateProgram();
    if (m_program == 0)
    {
        return false;
    }

    // In order to create a complete shader program, there must be a way to specify the list of things that will be linked together.
    // Shaders that are to be linked together in a program object must first be attached to that program object.
    // glAttachShader attaches the shader object to the program object.
    V(glAttachShader(m_program, vertexShader));
    V(glAttachShader(m_program, fragmentShader));
    V(glLinkProgram(m_program));
    
    V(glDetachShader(m_program, vertexShader));
    V(glDetachShader(m_program, fragmentShader));

    V(glDeleteShader(vertexShader));
    V(glDeleteShader(fragmentShader));
    
    return false;
}

GLuint OpenGLShader::CompileShader(GLenum shaderType, const char* shaderCodeStr) const
{
    // Creates an empty shader object.
    // A shader object is used to maintain the source code strings that define a shader.
    GLuint shader = 0;
    V(shader = glCreateShader(shaderType));

    // Replaces the source code in a shader object.
    V(glShaderSource(shader, 1, &shaderCodeStr, nullptr));

    // Compiles the source code strings that have been stored in the shader object.
    glCompileShader(shader);
    if (this->IsCompileSucceed(shader) == false)
    {
        core::Log("Failed to invoke glCompileShader. (%s)", GetShaderInfoLog(shader).c_str());
    }

    return shader;
}

bool OpenGLShader::IsCompileSucceed(GLuint shader) const
{
    GLint shaderCompileStatus;
    
    // Last parameter returns GL_TRUE if the last compile operation on shader was successful,
    // and GL_FALSE otherwise.
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileStatus);
    
    return (shaderCompileStatus == GL_TRUE) ? true : false;
}

std::string OpenGLShader::GetShaderInfoLog(GLuint shader) const
{
    std::string infoLog;
    
    int32_t infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    infoLog.resize(infoLogLength + 1);

    glGetShaderInfoLog(shader, infoLogLength, nullptr, &infoLog[0]);

    return infoLog;
}

} /* namespace graphics */
} /* namespace tgon */
