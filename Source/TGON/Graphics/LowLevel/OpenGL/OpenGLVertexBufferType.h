/**
 * @file    OpenGLVertexBufferType.h
 * @author  ggomdyu
 * @since   07/13/2018
 */

#pragma once
#include <GL/glew.h>

namespace tgon
{

enum class VertexFormatType
{
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
    Byte = GL_BYTE,
    UnsignedByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UnsignedShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UnsignedInt = GL_UNSIGNED_INT,
};

} /* namespace tgon */
