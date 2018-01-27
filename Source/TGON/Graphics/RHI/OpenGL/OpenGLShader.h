/**
 * @filename    OpenGLShader.h
 * @author      ggomdyu
 * @since       01/06/2018
 */

#pragma once
#include "OpenGLShader.h"

#include <string>
#include <cstdint>
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

class OpenGLShader
{
public:
    bool Initialize(const char* vsCodeStr, const char* fsCodeStr);

    void BeginScene();
    void EndScene();
    
    void BindAttributeLocation(const char* name, std::size_t location);
    int GetUniformLocation(const char* name) const;

    void SetParameter1f(const char* name, GLfloat f);
    void SetParameter2f(const char* name, GLfloat f1, GLfloat f2);
    void SetParameter3f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3);
    void SetParameter4f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    void SetParameterMatrix4fv(const char* name, const GLfloat* f);
    void SetParameter1f(int32_t location, GLfloat f);
    void SetParameter2f(int32_t location, GLfloat f1, GLfloat f2);
    void SetParameter3f(int32_t location, GLfloat f1, GLfloat f2, GLfloat f3);
    void SetParameter4f(int32_t location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    void SetParameterMatrix4fv(int32_t location, const GLfloat* f);
    void SetParameterSampler(int32_t location, int textureSlot, std::size_t sampler);

private:
    /* @brief   Links shders to the program object. */
    bool Link(GLuint vertexShader, GLuint fragmentShader);

    /**
     * @brief                       Compiles shader and return the handle of it.
     * @param [in]  shaderType      The type of shader: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc
     * @param [in]  shaderCodeStr   The source code of shader.
     * @return                      If the function fails, the return value is zero.
     */
    GLuint CompileShader(GLenum shaderType, const char* shaderCodeStr) const;

    /**
     * @brief   Checks shader was compiled successfully.
     * @return  Returns true if the compile was succeeded, false otherwise.
     */
    bool IsCompileSucceed(GLuint shader) const;

    std::string GetShaderInfoLog(GLuint shader) const;

public:
    GLuint m_program;
};

} /* namespace graphics */
} /* namespace tgon */
