/**
 * @file    OpenGLVertexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <GL/glew.h>
#include <vector>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{
    
struct VertexBufferLayoutDescriptor;

class TGON_API OpenGLVertexBuffer :
    private NonCopyable
{
/**@section Constructor */
public:
    OpenGLVertexBuffer();
    OpenGLVertexBuffer(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept;

/**@section Destructor */
public:
    ~OpenGLVertexBuffer();
    
/**@section Operator */
public:
    OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& rhs) noexcept;

/**@section Method */
protected:
    GLuint CreateVertexBufferHandle() const;
    void Destroy();

/**@section Variable */
protected:
    GLuint m_vertexBufferHandle;
    std::vector<VertexBufferLayoutDescriptor> m_vertexBufferLayoutDescs;
};

using PlatformVertexBuffer = OpenGLVertexBuffer;

} /* namespace tgon */
