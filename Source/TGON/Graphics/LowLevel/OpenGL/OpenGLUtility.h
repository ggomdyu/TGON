/**
 * @file    OpenGLUtility.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#include <cassert>
#include <GL/glew.h>

#if _DEBUG
#   define TGON_GL_ERROR_CHECK(expression)\
    {\
        expression;\
        assert(glGetError() == GL_NO_ERROR && "Failed to invoke GL Function.");\
    }
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif

namespace tgon
{
    
GLuint CreateRenderBuffer(GLenum format, int32_t width, int32_t height);
    
GLuint CreateFrameBuffer();
    
} /* namespace tgon */
