/**
 * @filename    OpenGLRHIUtility.h
 * @author      ggomdyu
 * @since       11/08/2017
 */

#pragma once

#ifdef _MSC_VER
#   ifdef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#   include <gl/GL.h>
#else
#   include <OpenGL/OpenGL.h>
#   include <OpenGL/gl.h>
#endif

#include "Graphics/RHI/Base/BaseRHIType.h"

namespace tgon
{
namespace rhi
{

inline GLenum ConvertPrimitiveTypeToNative(PrimitiveType primitiveType)
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

    return nativePrimitiveTable[static_cast<GLenum>(primitiveType)];
}

inline GLenum ConvertFillModeToNative(FillMode fillMode)
{
    static GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    return nativeFillModeTable[static_cast<GLenum>(fillMode)];
}

inline GLenum ConvertCullModeToNative(CullMode cullMode)
{
    static GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    return nativeCullModeTable[static_cast<GLenum>(cullMode)];
}

} /* namespace rhi */
} /* namespace tgon */
