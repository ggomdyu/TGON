/**
 * @filename    OpenGLGraphicsUtility.h
 * @author      ggomdyu
 * @since       02/16/2018
 */

#pragma once
#include <GL/glew.h>

#include "Core/Utility/Algorithm.h"

#include "../Generic/GenericGraphics.h"

namespace tgon
{

constexpr GLenum ConvertFillModeToNative(FillMode fillMode) noexcept
{
    constexpr GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    return nativeFillModeTable[UnderlyingCast(fillMode)];
}

constexpr GLenum ConvertCullModeToNative(CullMode cullMode) noexcept
{
    constexpr GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    return nativeCullModeTable[UnderlyingCast(cullMode)];
}

constexpr GLenum ConvertPrimitiveTypeToNative(PrimitiveType primitiveType) noexcept
{
    constexpr GLenum nativePrimitiveTypeTable[] =
    {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };

    return nativePrimitiveTypeTable[UnderlyingCast(primitiveType)];
}

} /* namespace tgon */