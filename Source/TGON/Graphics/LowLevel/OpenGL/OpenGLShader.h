/**
 * @file    OpenGLShader.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <string>
#include <cstdlib>

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace tgon
{

class TGON_API ShaderImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    ShaderImpl(const char* vertexShaderCode, const char* fragmentShaderCode);

/* @section Public destructor */
public:
    ~ShaderImpl();

/* @section Public method */
public:
    void Use();
    void Unuse();
    
    void SetParameter1f(const char* name, float f);
    void SetParameter2f(const char* name, float f1, float f2);
    void SetParameter3f(const char* name, float f1, float f2, float f3);
    void SetParameter4f(const char* name, float f1, float f2, float f3, float f4);
    void SetParameterMatrix4fv(const char* name, const float* f);
    void SetParameter1f(int32_t location, float f);
    void SetParameter2f(int32_t location, float f1, float f2);
    void SetParameter3f(int32_t location, float f1, float f2, float f3);
    void SetParameter4f(int32_t location, float f1, float f2, float f3, float f4);
    void SetParameterMatrix4fv(int32_t location, const float* f);
    void SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler);
    
    void BindAttributeLocation(const char* name, uint32_t location);
    int GetUniformLocation(const char* name) const;
    
    /* @brief                   Checks the shader was loaded successfully. */
    bool IsValid() const noexcept;

/* @section Private method */
private:
    /* @brief                   Links shaders to the program object. */
    bool LinkShadersToProgram(GLuint vertexShaderId, GLuint fragmentShaderId);

    /**
     * @brief                   Compiles shader and return the handle of it.
     * @param [in]  shaderType  The type of shader: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc
     * @param [in]  shaderCode  The source code of shader.
     * @return                  If the function fails, the return value is zero.
     */
    GLuint CompileShader(GLenum shaderType, const char* shaderCode) const;

    /**
     * @brief                   Checks shader was compiled successfully.
     * @return                  Returns true if the compile was succeeded, false otherwise.
     */
    bool IsShaderCompileSucceed(GLuint shaderId) const;

    std::string GetShaderInfoLog(GLuint shaderId) const;

/* @section Private variable */
public:
    GLuint m_programId;
};

} /* namespace tgon */
