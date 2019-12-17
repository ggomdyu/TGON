/**
 * @file    OpenGLDebug.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <cassert>
//#include <fmt/format.h>

#include "Diagnostics/Debug.h"

#if _DEBUG
#   define TGON_GL_ERROR_CHECK(expression)\
    expression;\
    if (glGetError() == GL_NO_ERROR)\
    {\
        tgon::Debug::WriteLine("Failed to invoke GL Function."); \
    }
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif
#endif
