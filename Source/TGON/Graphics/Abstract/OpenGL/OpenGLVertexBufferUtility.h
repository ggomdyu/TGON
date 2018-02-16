/**
 * @filename    OpenGLVertexBufferUtility.h
 * @author      ggomdyu
 * @since       02/12/2018
 */

#pragma once
#include "OpenGLVertexBufferType.h"

#include "../Generic/GenericVertexBufferType.h"

#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

constexpr GLenum ConvertVertexFormatTypeToNative(VertexFormatType vertexFormatType)
{
    constexpr GLenum nativeVertexFormatTypeTable[] =
    {
        GL_FLOAT,
        GL_DOUBLE,
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT,
    };

    return nativeVertexFormatTypeTable[static_cast<std::size_t>(vertexFormatType)];
}

inline OpenGLVertexBufferDesc ConvertVertexBufferDescToNative(VertexBufferDesc vertexBufferDesc)
{
    return OpenGLVertexBufferDesc{
        static_cast<GLuint>(vertexBufferDesc.attribute), 
        static_cast<GLint>(vertexBufferDesc.dimension), 
        ConvertVertexFormatTypeToNative(vertexBufferDesc.type),
        static_cast<GLboolean>(vertexBufferDesc.normalized),
        static_cast<GLsizei>(vertexBufferDesc.stride),
        reinterpret_cast<const void*>(vertexBufferDesc.offset)
    };
}

} /* namespace graphics */
} /* namespace tgon */
