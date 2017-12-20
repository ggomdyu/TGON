/**
 * @filename    OpenGLShaderUtility.h
 * @author      ggomdyu
 * @since       12/19/2017
 */

#pragma once
#include <GL/glew.h>
#include <boost/predef/os.h>
#include <cstdint>

#include "Core/Platform/Debug.h"

#if _DEBUG
#define GL_ERROR_CHECK(expression)\
{\
    expression;\
    GLenum errorCode = glGetError();\
    if (errorCode != GL_NO_ERROR)\
    {\
        platform::Log("OpenGL error occured. (Code: %d, File:%s, Function:%s, Line:%d)", errorCode, __FILE__, __FUNCTION__, __LINE__);\
    }\
}
#else
#define GL_ERROR_CHECK(expression) expression;
#endif

namespace tgon
{
namespace render
{

GLuint CreateShader(GLenum shaderType, const char* shaderStr);

} /* namespace render */
} /* namespace tgon */