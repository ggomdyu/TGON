/**
 * @file    OpenGLVertexBufferType.h
 * @author  ggomdyu
 * @since   02/12/2018
 */

#pragma once
#include <GL/glew.h>

namespace tgon
{

struct OpenGLVertexBufferDesc
{
    GLuint attribute;
    GLint dimension;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* offset;
};

} /* namespace tgon */
