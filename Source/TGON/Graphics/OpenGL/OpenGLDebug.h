/**
 * @file    OpenGLDebug.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <fmt/format.h>

#include "Diagnostics/Debug.h"

#if defined(_DEBUG) || !defined(NDEBUG)
#   define TGON_GL_ERROR_CHECK(expression)\
    expression;\
    {\
        auto errorCode = glGetError();\
        if (errorCode != GL_NO_ERROR)\
        {\
            tgon::Debug::WriteLine(fmt::format("Failed to invoke GL Function. (Code:{0}, Expression:{1})", errorCode, #expression));\
        }\
    }
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif
#endif
