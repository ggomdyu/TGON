#include "PrecompiledHeader.pch"

#include <cassert>

#include "Core/Debug/Log.h"

#include "OpenGLShader.h"
#include "OpenGLUtility.h"

namespace tgon
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
    TGON_GL_ERROR_CHECK(glUseProgram(m_program));
}

void OpenGLShader::Unuse()
{
    TGON_GL_ERROR_CHECK(glUseProgram(0));
}

void OpenGLShader::BindAttributeLocation(const char* name, uint32_t index)
{
    TGON_GL_ERROR_CHECK(glBindAttribLocation(m_program, index, name));
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
    TGON_GL_ERROR_CHECK(glUniform1f(location, f));
}

void OpenGLShader::SetParameter2f(int32_t location, float f1, float f2)
{
    TGON_GL_ERROR_CHECK(glUniform2f(location, f1, f2));
}

void OpenGLShader::SetParameter3f(int32_t location, float f1, float f2, GLfloat f3)
{
    TGON_GL_ERROR_CHECK(glUniform3f(location, f1, f2, f3));
}

void OpenGLShader::SetParameter4f(int32_t location, float f1, float f2, float f3, float f4)
{
    TGON_GL_ERROR_CHECK(glUniform4f(location, f1, f2, f3, f4));
}

void OpenGLShader::SetParameterMatrix4fv(int32_t location, const float* f)
{
    TGON_GL_ERROR_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, f));
}

void OpenGLShader::SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler)
{
    TGON_GL_ERROR_CHECK(glActiveTexture(GL_TEXTURE0 + textureSlot));

    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, sampler));
    TGON_GL_ERROR_CHECK(glUniform1i(location, sampler));
}

bool OpenGLShader::IsValid() const noexcept
{
    return m_program;
}

bool OpenGLShader::LinkShadersToProgram(GLuint vertexShader, GLuint fragmentShader)
{
    // Creates an empty program object.
    TGON_GL_ERROR_CHECK(m_program = glCreateProgram());
    if (m_program == 0)
    {
        return false;
    }

    // In order to create a complete shader program, there must be a way to specify the list of things that will be linked together.
    // Shaders that are to be linked together in a program object must first be attached to that program object.
    // glAttachShader attaches the shader object to the program object.
    TGON_GL_ERROR_CHECK(glAttachShader(m_program, vertexShader));
    TGON_GL_ERROR_CHECK(glAttachShader(m_program, fragmentShader));
    TGON_GL_ERROR_CHECK(glLinkProgram(m_program));

    TGON_GL_ERROR_CHECK(glDetachShader(m_program, vertexShader));
    TGON_GL_ERROR_CHECK(glDetachShader(m_program, fragmentShader));

    TGON_GL_ERROR_CHECK(glDeleteShader(vertexShader));
    TGON_GL_ERROR_CHECK(glDeleteShader(fragmentShader));
    
    return true;
}

GLuint OpenGLShader::CompileShader(GLenum shaderType, const char* shaderCode) const
{
    // Creates an empty shader object.
    // A shader object is used to maintain the source code strings that define a shader.
    GLuint shader = 0;
    TGON_GL_ERROR_CHECK(shader = glCreateShader(shaderType));

    // Replaces the source code in a shader object.
    TGON_GL_ERROR_CHECK(glShaderSource(shader, 1, &shaderCode, nullptr));

    // Compiles the source code strings that have been stored in the shader object.
    TGON_GL_ERROR_CHECK(glCompileShader(shader));
    if (this->IsShaderCompileSucceed(shader) == false)
    {
        Log(LogLevel::Warning, "Failed to invoke glCompileShader. (%s)", GetShaderInfoLog(shader).c_str());
        return 0;
    }

    return shader;
}

bool OpenGLShader::IsShaderCompileSucceed(GLuint shader) const
{
    GLint shaderCompileStatus;
    
    // Last parameter returns GL_TRUE if the last compile operation on shader was successful,
    // and GL_FALSE otherwise.
    TGON_GL_ERROR_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileStatus));
    
    return (shaderCompileStatus == GL_TRUE) ? true : false;
}

std::string OpenGLShader::GetShaderInfoLog(GLuint shader) const
{
    std::string infoLog;
    int32_t infoLogLen;
    
    TGON_GL_ERROR_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen));
    
    infoLog.resize(infoLogLen + 1);

    TGON_GL_ERROR_CHECK(glGetShaderInfoLog(shader, infoLogLen, nullptr, &infoLog[0]));

    return infoLog;
}

} /* namespace tgon */