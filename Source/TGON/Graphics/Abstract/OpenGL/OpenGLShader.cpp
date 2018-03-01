#include "PrecompiledHeader.pch"

#include "OpenGLShader.h"

#include "Core/Debug/Log.h"

#include <cassert>

namespace tgon
{
namespace graphics
{

OpenGLShader::OpenGLShader(const char* vertexShaderCode, const char* fragmentShaderCode) :
    m_program(0)
{
    assert(vertexShaderCode != nullptr);
    assert(fragmentShaderCode != nullptr);

    GLuint vertexShader = this->CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    if (vertexShader == 0)
    {
        return;
    }

    GLuint fragmentShader = this->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    if (fragmentShader == 0)
    {
        return;
    }
    
    this->LinkShadersToProgram(vertexShader, fragmentShader);
}

void OpenGLShader::Use()
{
    glUseProgram(m_program);
}

void OpenGLShader::Unuse()
{
    glUseProgram(0);
}

void OpenGLShader::BindAttributeLocation(const char* name, uint32_t index)
{
    glBindAttribLocation(m_program, index, name);
}

int OpenGLShader::GetUniformLocation(const char* name) const
{
    return glGetUniformLocation(m_program, name);
}

void OpenGLShader::SetParameter1f(const char* name, float f)
{
    this->SetParameter1f(this->GetUniformLocation(name), f);
}

void OpenGLShader::SetParameter2f(const char* name, float f1, float f2)
{
    this->SetParameter2f(this->GetUniformLocation(name), f1, f2);
}

void OpenGLShader::SetParameter3f(const char* name, float f1, float f2, float f3)
{
    this->SetParameter3f(this->GetUniformLocation(name), f1, f2, f3);
}

void OpenGLShader::SetParameter4f(const char* name, float f1, float f2, float f3, float f4)
{
    this->SetParameter4f(this->GetUniformLocation(name), f1, f2, f3, f4);
}

void OpenGLShader::SetParameterMatrix4fv(const char* name, const float* f)
{
    this->SetParameterMatrix4fv(this->GetUniformLocation(name), f);
}

void OpenGLShader::SetParameter1f(int32_t location, float f)
{
    glUniform1f(location, f);
}

void OpenGLShader::SetParameter2f(int32_t location, float f1, float f2)
{
    glUniform2f(location, f1, f2);
}

void OpenGLShader::SetParameter3f(int32_t location, float f1, float f2, GLfloat f3)
{
    glUniform3f(location, f1, f2, f3);
}

void OpenGLShader::SetParameter4f(int32_t location, float f1, float f2, float f3, float f4)
{
    glUniform4f(location, f1, f2, f3, f4);
}

void OpenGLShader::SetParameterMatrix4fv(int32_t location, const float* f)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, f);
}

void OpenGLShader::SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);

    glBindTexture(GL_TEXTURE_2D, sampler);
    glUniform1i(location, sampler);
}

bool OpenGLShader::IsValid() const noexcept
{
    return m_program;
}

bool OpenGLShader::LinkShadersToProgram(GLuint vertexShader, GLuint fragmentShader)
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
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);
    
    glDetachShader(m_program, vertexShader);
    glDetachShader(m_program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return true;
}

GLuint OpenGLShader::CompileShader(GLenum shaderType, const char* shaderCodeStr) const
{
    // Creates an empty shader object.
    // A shader object is used to maintain the source code strings that define a shader.
    GLuint shader = 0;
    shader = glCreateShader(shaderType);

    // Replaces the source code in a shader object.
    glShaderSource(shader, 1, &shaderCodeStr, nullptr);

    // Compiles the source code strings that have been stored in the shader object.
    glCompileShader(shader);
    if (this->IsShaderCompileSucceed(shader) == false)
    {
        core::Log("Failed to invoke glCompileShader. (%s)", GetShaderInfoLog(shader).c_str());
        return 0;
    }

    return shader;
}

bool OpenGLShader::IsShaderCompileSucceed(GLuint shader) const
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
