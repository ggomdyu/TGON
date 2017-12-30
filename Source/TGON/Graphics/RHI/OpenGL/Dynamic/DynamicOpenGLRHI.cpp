#include "PrecompiledHeader.pch"

#include <atomic>
#include <GL/glew.h>

#include "Core/Math/Color.h"
#include "Core/Platform/Debug.h"

#include "../../RHIType.h"

#include "DynamicOpenGLRHI.h"

#if _DEBUG
#   define GL_ERROR_CHECK(expression)\
    {\
        expression;\
        GLenum errorCode = glGetError();\
        if (errorCode != GL_NO_ERROR)\
        {\
            platform::Log("OpenGL error occured. (Code: %d, File:%s, Function:%s, Line:%d)", errorCode, __FILE__, __FUNCTION__, __LINE__);\
        }\
    }
#else
#   define GL_ERROR_CHECK(expression) expression;
#endif


namespace tgon
{
namespace rhi
{

class GLProgram
{
public:
    bool Initialize(const char* vertexShaderStr, const char* fragmentShaderStr);
    bool Initialize(GLuint vertexShaderHandle, GLuint fragmentShaderHandle);

    GLuint GetProgramHandle() const;

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

bool GLProgram::Initialize(GLuint vertexShaderHandle, GLuint fragmentShaderHandle)
{
    // Creates shader program object.
    m_shaderProgram = glCreateProgram();
    if (m_shaderProgram == 0)
    {
        return false;
    }

    // Attachs shaders to program.
    GL_ERROR_CHECK(glAttachShader(m_shaderProgram, vertexShaderHandle));
    GL_ERROR_CHECK(glAttachShader(m_shaderProgram, fragmentShaderHandle));
    {
        GL_ERROR_CHECK(glLinkProgram(m_shaderProgram));
    }
    GL_ERROR_CHECK(glDetachShader(m_shaderProgram, vertexShaderHandle));
    GL_ERROR_CHECK(glDetachShader(m_shaderProgram, fragmentShaderHandle));

    GL_ERROR_CHECK(glDeleteShader(vertexShaderHandle));
    GL_ERROR_CHECK(glDeleteShader(fragmentShaderHandle));
    return false;
}

GLuint GLProgram::GetProgramHandle() const
{
    return m_shaderProgram;
}

GLuint GLProgram::CreateVertexShader(const char* vertexShaderStr) const
{
    GLuint vertexShader=0;
    GL_ERROR_CHECK(vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderStr));

    return vertexShader;
}

GLuint GLProgram::CreateFragmentShader(const char* fragmentShaderStr) const
{
    GLuint fragmentShader=0;
    GL_ERROR_CHECK(fragmentShader = CreateShader(GL_VERTEX_SHADER, fragmentShaderStr));

    return fragmentShader;
}

GLuint CreateShader(GLenum shaderType, const char* shaderStr)
{
    GLuint shader = 0;
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

OpenGLRHI::OpenGLRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode) :
    m_context(window, videoMode)
{
}

void OpenGLRHI::SetClearColor(const math::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRHI::SetFillMode(FillMode fillMode)
{
    static GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    glPolygonMode(GL_FRONT_AND_BACK, nativeFillModeTable[static_cast<GLenum>(fillMode)]);
}

void OpenGLRHI::SetCullMode(CullMode cullMode)
{
    static GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    glFrontFace(nativeCullModeTable[static_cast<GLenum>(cullMode)]);
}

void OpenGLRHI::EnalbleDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRHI::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

Shader OpenGLRHI::CreateShader(const char* shaderCode)
{
    return nullptr;
}

VideoBuffer OpenGLRHI::CreateVideoBuffer(VideoBufferType videoBufferType, std::size_t bufferSize)
{
    static std::atomic<int> bufferIndex;

    GLuint videoBuffer;
    glCreateBuffers(bufferIndex++, &videoBuffer);

    return reinterpret_cast<VideoBuffer>(videoBuffer);
}

void OpenGLRHI::BeginScene(PrimitiveType primitiveType)
{
    static GLenum nativePrimitiveTable[] =
    {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };

    glBegin(nativePrimitiveTable[static_cast<GLenum>(primitiveType)]);
}

void OpenGLRHI::EndScene()
{
    glEnd();
}

void OpenGLRHI::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRHI::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRHI::SwapBuffer()
{
    ::SwapBuffers(m_context.dcHandle);
}

} /* namespace rhi */
} /* namespace tgon */