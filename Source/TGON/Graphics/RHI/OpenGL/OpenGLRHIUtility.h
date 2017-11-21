/**
 * @filename    OpenGLRHIFwd.h
 * @author      ggomdyu
 * @since       11/08/2017
 */

#pragma once
#include <OpenGL/gl.h>

#include "Graphics/RHI/Base/BaseRHIType.h"

namespace tgon
{
namespace rhi
{
namespace gl
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
        GL_CW,
        GL_CCW
    };

    return nativeCullModeTable[static_cast<GLenum>(cullMode)];
}

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */
