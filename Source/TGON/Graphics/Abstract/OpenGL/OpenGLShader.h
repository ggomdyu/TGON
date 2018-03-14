/**
 * @filename    OpenGLShader.h
 * @author      ggomdyu
 * @since       01/06/2018
 */

#pragma once
#include "../Generic/GenericShader.h"

#include <string>
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

class OpenGLShader :
    public GenericShader
{
/* @section Public constructor */
public:
    OpenGLShader(const char* vertexShaderCode, const char* fragmentShaderCode);

/* @section Public destructor */
public:
    virtual ~OpenGLShader() override = default;

/* @section Public method */
public:
    virtual void Use() final override;
    virtual void Unuse() final override;
    
    virtual void SetParameter1f(const char* name, float f) final override;
    virtual void SetParameter2f(const char* name, float f1, float f2) final override;
    virtual void SetParameter3f(const char* name, float f1, float f2, float f3) final override;
    virtual void SetParameter4f(const char* name, float f1, float f2, float f3, float f4) final override;
    virtual void SetParameterMatrix4fv(const char* name, const float* f) final override;
    virtual void SetParameter1f(int32_t location, float f) final override;
    virtual void SetParameter2f(int32_t location, float f1, float f2) final override;
    virtual void SetParameter3f(int32_t location, float f1, float f2, float f3) final override;
    virtual void SetParameter4f(int32_t location, float f1, float f2, float f3, float f4) final override;
    virtual void SetParameterMatrix4fv(int32_t location, const float* f) final override;
    virtual void SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler) final override;
    
    virtual void BindAttributeLocation(const char* name, uint32_t location) final override;
    virtual int GetUniformLocation(const char* name) const final override;
    
    /* @brief   Checks the shader was loaded successfully. */
    virtual bool IsValid() const noexcept final override;

/* @section Private method */
private:
    /* @brief   Links shaders to the program object. */
    bool LinkShadersToProgram(GLuint vertexShader, GLuint fragmentShader);

    /**
     * @brief                   Compiles shader and return the handle of it.
     * @param [in]  shaderType  The type of shader: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc
     * @param [in]  shaderCode  The source code of shader.
     * @return                  If the function fails, the return value is zero.
     */
    GLuint CompileShader(GLenum shaderType, const char* shaderCode) const;

    /**
     * @brief   Checks shader was compiled successfully.
     * @return  Returns true if the compile was succeeded, false otherwise.
     */
    bool IsShaderCompileSucceed(GLuint shader) const;

    std::string GetShaderInfoLog(GLuint shader) const;

/* @section Private variable */
public:
    GLuint m_program;
};

class Shader : public OpenGLShader
{
/* @section Public constructor */
public:
    using OpenGLShader::OpenGLShader;
    
/* @section Public destructor */
public:
    virtual ~Shader() final override = default;
};

} /* namespace graphics */
} /* namespace tgon */