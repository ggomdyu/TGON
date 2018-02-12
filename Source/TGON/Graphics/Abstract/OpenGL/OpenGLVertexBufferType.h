/**
 * @filename    OpenGLVertexBufferType.h
 * @author      ggomdyu
 * @since       02/12/2018
 */

#pragma once
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

struct OpenGLVertexBufferDesc
{
    GLint attribute;
    GLint dimension;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* offset;
};

} /* namespace graphics */
} /* namespace tgon */