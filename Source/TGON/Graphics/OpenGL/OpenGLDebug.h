/**
 * @file    OpenGLDebug.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <cassert>

#if _DEBUG
#   define TGON_GL_ERROR_CHECK(expression)\
    expression;\
    assert(glGetError() == GL_NO_ERROR && "Failed to invoke GL Function.");
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif
#endif
