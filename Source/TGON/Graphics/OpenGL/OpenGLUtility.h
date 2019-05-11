/**
 * @file    OpenGLUtility.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#include <cassert>
#include <GL/glew.h>

#include "Diagnostics/Log.h"

#if _DEBUG
#   define TGON_GL_ERROR_CHECK(expression)\
    {\
        expression;\
        \
        auto glErrorCode = glGetError();\
        tgon::Assert(glErrorCode == GL_NO_ERROR, "Failed to invoke GL Function. (Code: %d)", glErrorCode);\
    }
#else
#   define TGON_GL_ERROR_CHECK(expression) expression
#endif
