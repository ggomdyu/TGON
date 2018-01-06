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
    bool Initialize(const char* vertexShaderCodeStr, const char* fragmentShaderCodeStr);

    void BeginScene();
    void EndScene();
    
    void BindAttributeLocation(const char* name, std::size_t location);
    int GetUniformLocation(const char* name) const;

    void SetParameter1f(const char* name, GLfloat f);
    void SetParameter2f(const char* name, GLfloat f1, GLfloat f2);
    void SetParameter3f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3);
    void SetParameter4f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    void SetParameter1f(std::size_t location, GLfloat f);
    void SetParameter2f(std::size_t location, GLfloat f1, GLfloat f2);
    void SetParameter3f(std::size_t location, GLfloat f1, GLfloat f2, GLfloat f3);
    void SetParameter4f(std::size_t location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    void SetParameterSampler(std::size_t location, int textureSlot, std::size_t sampler);

private:
    /* @brief   Links shders to the program object. */
    bool Link(GLuint vertexShader, GLuint fragmentShader);

    /**
     * @brief                   Compiles shader and return the handle of it.
     * @param [in]  shaderType  The type of shader: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc
     * @param [in]  shaderStr   The source code of shader.
     * @return                  If the function fails, the return value is zero.
     */
    GLuint CompileShader(GLenum shaderType, const char* shaderCodeStr) const;

    /**
     * @brief   Checks shader was compiled successfully.
     * @return  Returns true if the compile was succeeded, false otherwise.
     */
    bool IsCompileSucceed(GLuint shader) const;

    std::string GetShaderInfoLog(GLuint shader) const;

private:
    GLuint m_program;
};

} /* namespace graphics */
} /* namespace tgon */