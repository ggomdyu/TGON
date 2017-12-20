#include "PrecompiledHeader.pch"
#include "OpenGLUtility.h"


namespace tgon
{
namespace render
{

class GLProgram
{
public:
    bool Initialize(const char* vertexShaderStr, const char* fragmentShaderStr);
    bool Initialize(GLuint vertexShader, GLuint fragmentShader);

private:
    GLuint CreateVertexShader(const char* vertexShaderStr) const;
    GLuint CreateFragmentShader(const char* fragmentShaderStr) const;

private:
    GLuint m_shaderProgram;
};

bool GLProgram::Initialize(const char* vertexShaderStr, const char* fragmentShaderStr)
{
    // Creates shaders.
    GLuint vertexShader = this->CreateVertexShader(vertexShaderStr);
    if (vertexShader == 0)
    {
        return false;
    }

    GLuint fragmentShader = this->CreateFragmentShader(fragmentShaderStr);
    if (fragmentShader == 0)
    {
        return false;
    }

    // Creates a program.
    if (this->Initialize(vertexShader, fragmentShader) == false)
    {
        return false;
    }
}

bool GLProgram::Initialize(GLuint vertexShader, GLuint fragmentShader)
{
    // Creates shader program object.
    GL_ERROR_CHECK(m_shaderProgram = glCreateProgram());
    if (m_shaderProgram == 0)
    {
        return false;
    }

    // Attachs shaders to program.
    GL_ERROR_CHECK(glAttachShader(m_shaderProgram, vertexShader));
    GL_ERROR_CHECK(glAttachShader(m_shaderProgram, fragmentShader));
    {
        GL_ERROR_CHECK(glLinkProgram(m_shaderProgram));
    }
    GL_ERROR_CHECK(glDetachShader(m_shaderProgram, vertexShader));
    GL_ERROR_CHECK(glDetachShader(m_shaderProgram, fragmentShader));

    GL_ERROR_CHECK(glDeleteShader(vertexShader));
    GL_ERROR_CHECK(glDeleteShader(fragmentShader));
    return false;
}

GLuint GLProgram::CreateVertexShader(const char* vertexShaderStr) const
{
    GLuint vertexShader;
    GL_ERROR_CHECK(vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderStr));

    return vertexShader;
}

GLuint GLProgram::CreateFragmentShader(const char* fragmentShaderStr) const
{
    GLuint fragmentShader;
    GL_ERROR_CHECK(fragmentShader = CreateShader(GL_VERTEX_SHADER, fragmentShaderStr));

    return fragmentShader;
}

GLuint CreateShader(GLenum shaderType, const char* shaderStr)
{
    GLuint shader;
    GL_ERROR_CHECK(shader = glCreateShader(shaderType));

    // Set source of shader.
    glShaderSource(shader, 1, &shaderStr, nullptr);

    // Then, compile it.
    glCompileShader(shader);

    // Lastly, Check wheter compile is succeed.
    // If compile was failed, then record detail log.
    GL_ERROR_CHECK(shader);

    return shader;
}

} /* namespace render */
} /* namespace tgon */