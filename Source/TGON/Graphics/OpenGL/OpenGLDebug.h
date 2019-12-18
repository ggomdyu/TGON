/**
 * @file    OpenGLDebug.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <fmt/format.h>

#include "Diagnostics/Debug.h"

#if _DEBUG
#   define TGON_GL_ERROR_CHECK(expression)\
    expression;\
    if (glGetError() != GL_NO_ERROR)\
    {\
        tgon::Debug::WriteLine(fmt::fotmat("Failed to invoke GL Function. (Code:{0}, Expression:{1})", glGetError(), #expression); \
    }
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif
#endif
