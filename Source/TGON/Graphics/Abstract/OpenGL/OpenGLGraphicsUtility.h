/**
 * @filename    OpenGLGraphicsUtility.h
 * @author      ggomdyu
 * @since       02/16/2018
 */

#pragma once
#include "../Generic/GenericGraphics.h"

#include "Core/Utility/Enumerator.h"

namespace tgon
{
namespace graphics
{

constexpr GLenum ConvertFillModeToNative(FillMode fillMode) noexcept
{
    constexpr GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    return nativeFillModeTable[core::ToUnderlying(fillMode)];
}

constexpr GLenum ConvertCullModeToNative(CullMode cullMode) noexcept
{
    constexpr GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    return nativeCullModeTable[core::ToUnderlying(cullMode)];
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

    return nativePrimitiveTypeTable[core::ToUnderlying(primitiveType)];
}

} /* namespace graphics */
} /* namespace tgon */