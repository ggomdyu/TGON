/**
 * @file    OpenGLDebug.h
 * @author  ggomdyu
 * @since   04/01/2018
 */

#pragma once
#include <fmt/format.h>

#include "Diagnostics/Debug.h"

#if defined(_DEBUG) || !defined(NDEBUG)
#   define TGON_AL_ERROR_CHECK(expression)\
    expression;\
    {\
        auto errorCode = alGetError();\
        if (errorCode != AL_NO_ERROR)\
        {\
            tgon::Debug::WriteLine(fmt::format("Failed to invoke AL Function. (Code:{0}, Expression:{1})", errorCode, #expression));\
        }\
    }
#else
#   define TGON_AL_ERROR_CHECK(expression) expression;
#endif