#include "PrecompiledHeader.pch"

#include "OpenGLDynamicRHI.h"

#include "../RHIType.h"

#include "Core/Math/Color.h"
#include "Core/Platform/Debug.h"
#include "Graphics/RHI/RHIType.h"
 
#include <atomic>
#include <GL/glew.h>

#if _DEBUG
#   define GL_ERROR_CHECK(expression)\
    {\
        expression;\
        GLenum errorCode = glGetError();\
        if (errorCode != GL_NO_ERROR)\
        {\
            core::Log("OpenGL error occured. (Code: %d, File:%s, Function:%s, Line:%d)", errorCode, __FILE__, __FUNCTION__, __LINE__);\
        }\
    }
#else
#   define GL_ERROR_CHECK(expression) expression;
#endif


namespace tgon
{
namespace graphics
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

    return true;
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
    //GL_ERROR_CHECK(vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderStr));

    return vertexShader;
}

GLuint GLProgram::CreateFragmentShader(const char* fragmentShaderStr) const
{
    GLuint fragmentShader=0;
    /*GL_ERROR_CHECK(fragmentShader = CreateShader(GL_VERTEX_SHADER, fragmentShaderStr));*/

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

OpenGLDynamicRHI::OpenGLDynamicRHI(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode) :
    m_context(std::make_unique<OpenGLContext>(window, videoMode))
{
}

void OpenGLDynamicRHI::SetClearColor(const core::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLDynamicRHI::SetFillMode(FillMode fillMode)
{
    static GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    glPolygonMode(GL_FRONT_AND_BACK, nativeFillModeTable[static_cast<GLenum>(fillMode)]);
}

void OpenGLDynamicRHI::SetCullMode(CullMode cullMode)
{
    static GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    glFrontFace(nativeCullModeTable[static_cast<GLenum>(cullMode)]);
}

void OpenGLDynamicRHI::EnalbleDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLDynamicRHI::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

//VideoBuffer OpenGLDynamicRHI::CreateVideoBuffer(VideoBufferType videoBufferType, std::size_t bufferSize)
//{
//    static std::atomic<int> bufferIndex;
//
//    GLuint videoBuffer;
//    glCreateBuffers(bufferIndex++, &videoBuffer);
//
//    return reinterpret_cast<VideoBuffer>(videoBuffer);
//}

void OpenGLDynamicRHI::BeginScene(PrimitiveType primitiveType)
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

void OpenGLDynamicRHI::EndScene()
{
    glEnd();
}

void OpenGLDynamicRHI::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLDynamicRHI::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDynamicRHI::SwapBuffer()
{
    ::SwapBuffers(m_context->dcHandle);
}

} /* namespace graphics */
} /* namespace tgon */