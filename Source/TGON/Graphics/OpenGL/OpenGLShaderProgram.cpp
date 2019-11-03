#include "PrecompiledHeader.h"

#include <cassert>
#include <sstream>

#include "Diagnostics/Debug.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"

#include "OpenGLDebug.h"

#include "../ShaderProgram.h"

namespace tgon
{
namespace
{

OpenGLShaderProgram* g_lastUsedShaderProgram;

GLuint CreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
    // Creates an empty program object.
    GLuint programId = 0;
    TGON_GL_ERROR_CHECK(programId = glCreateProgram());
    if (programId == 0)
    {
        return 0;
    }

    // In order to create a complete shader program, there must be a way to specify the list of things that will be linked together.
    // Shaders that are to be linked together in a program object must first be attached to that program object.
    // glAttachShader attaches the shader object to the program object.
    TGON_GL_ERROR_CHECK(glAttachShader(programId, vertexShaderId));
    TGON_GL_ERROR_CHECK(glAttachShader(programId, fragmentShaderId));
    TGON_GL_ERROR_CHECK(glLinkProgram(programId));

    TGON_GL_ERROR_CHECK(glDetachShader(programId, vertexShaderId));
    TGON_GL_ERROR_CHECK(glDetachShader(programId, fragmentShaderId));

    TGON_GL_ERROR_CHECK(glDeleteShader(vertexShaderId));
    TGON_GL_ERROR_CHECK(glDeleteShader(fragmentShaderId));
    
    return programId;
}

std::string GetShaderLog(GLuint shaderId)
{
    int32_t infoLogLen;
    TGON_GL_ERROR_CHECK(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLen));

    std::string infoLog;
    infoLog.resize(infoLogLen + 1);
    TGON_GL_ERROR_CHECK(glGetShaderInfoLog(shaderId, infoLogLen, nullptr, &infoLog[0]));

    return infoLog;
}

bool IsShaderCompileSucceed(GLuint shaderId)
{
    GLint shaderCompileStatus;
    TGON_GL_ERROR_CHECK(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompileStatus));

    return shaderCompileStatus == GL_TRUE;
}

GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
    GLuint shaderId = 0;
    TGON_GL_ERROR_CHECK(shaderId = glCreateShader(shaderType));
    TGON_GL_ERROR_CHECK(glShaderSource(shaderId, 1, &shaderCode, nullptr));

    // Compile the shader code that stored in the shader object.
    TGON_GL_ERROR_CHECK(glCompileShader(shaderId));
    if (IsShaderCompileSucceed(shaderId) == false)
    {
        std::stringstream ss;
        ss << "Failed to invoke glCompileShader. (" << GetShaderLog(shaderId) << ")";

        Debug::WriteLine(ss.str());
        return 0;
    }

    return shaderId;
}

} /* namespace */

OpenGLShaderProgram::OpenGLShaderProgram(GLuint programId) noexcept :
    m_programId(programId)
{
}

OpenGLShaderProgram::OpenGLShaderProgram(OpenGLShaderProgram&& rhs) noexcept :
    m_programId(rhs.m_programId)
{
    rhs.m_programId = 0;
}
    
OpenGLShaderProgram& OpenGLShaderProgram::operator=(OpenGLShaderProgram&& rhs) noexcept
{
    m_programId = rhs.m_programId;
    
    rhs.m_programId = 0;
    
    return *this;
}

GLuint OpenGLShaderProgram::GetProgramId() const noexcept
{
    return m_programId;
}

ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) :
    OpenGLShaderProgram([&]()
    {
        GLuint vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
        GLuint fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
        return CreateShaderProgram(vertexShaderId, fragmentShaderId);
    } ())
{
    this->UpdateUniformLocationCache();
}

void ShaderProgram::Use()
{
    if (g_lastUsedShaderProgram == this)
    {
        return;
    }
    
    this->ResetUniformCache();
    TGON_GL_ERROR_CHECK(glUseProgram(m_programId));
    
    g_lastUsedShaderProgram = this;
}

void ShaderProgram::Unuse()
{
    TGON_GL_ERROR_CHECK(glUseProgram(0));
    
    g_lastUsedShaderProgram = nullptr;
}

void ShaderProgram::BindAttributeLocation(const char* name, uint32_t index)
{
    TGON_GL_ERROR_CHECK(glBindAttribLocation(m_programId, index, name));
}

int32_t ShaderProgram::GetUniformLocation(const char* name) const
{
    return static_cast<int32_t>(glGetUniformLocation(m_programId, name));
}

void ShaderProgram::SetParameter1f(int32_t location, float f)
{
    auto& uniformCache = m_uniformCache[location].x;
    if (uniformCache == f)
    {
        return;
    }
    
    uniformCache = f;
    
    TGON_GL_ERROR_CHECK(glUniform1f(location, f));
}

void ShaderProgram::SetParameter2f(int32_t location, float f1, float f2)
{
    auto uniformCache = reinterpret_cast<Vector2*>(&m_uniformCache[location].x);
    auto v = Vector2(f1, f2);
    if (*uniformCache == v)
    {
        return;
    }
    
    *uniformCache = v;
    
    TGON_GL_ERROR_CHECK(glUniform2f(location, f1, f2));
}

void ShaderProgram::SetParameter3f(int32_t location, float f1, float f2, float f3)
{
    auto uniformCache = reinterpret_cast<Vector3*>(&m_uniformCache[location].x);
    auto v = Vector3(f1, f2, f3);
    if (*uniformCache == v)
    {
        return;
    }
    
    *uniformCache = v;
    
    TGON_GL_ERROR_CHECK(glUniform3f(location, f1, f2, f3));
}

void ShaderProgram::SetParameter4f(int32_t location, float f1, float f2, float f3, float f4)
{
    auto uniformCache = reinterpret_cast<Vector4*>(&m_uniformCache[location].x);
    auto v = Vector4(f1, f2, f3, f4);
    if (*uniformCache == v)
    {
        return;
    }
    
    *uniformCache = v;
    
    TGON_GL_ERROR_CHECK(glUniform4f(location, f1, f2, f3, f4));
}

void ShaderProgram::SetParameterMatrix4fv(int32_t location, const float* f)
{
    TGON_GL_ERROR_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, f));
}

void ShaderProgram::SetParameterSampler(int32_t location, uint32_t textureUnit, uint32_t texture)
{
    TGON_GL_ERROR_CHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));

    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
    TGON_GL_ERROR_CHECK(glUniform1i(location, texture));
}

void ShaderProgram::Destroy()
{
    if (m_programId != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteProgram(m_programId));
        m_programId = 0;
    }
}

} /* namespace tgon */
