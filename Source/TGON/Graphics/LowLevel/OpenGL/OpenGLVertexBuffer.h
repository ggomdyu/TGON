/**
 * @file    OpenGLVertexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>
#include <GL/glew.h>

namespace tgon
{

struct VertexBufferDesc;

class VertexBufferImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    VertexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);

/* @section Public destructor */
public:
    ~VertexBufferImpl();

/* @section Public method */
public:
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    std::size_t GetDataBytes() const noexcept;
    void Use();
    void Unuse();
    bool IsValid() const noexcept;
    bool IsDynamicUsage() const noexcept;

/* @section Private method */
private:
    GLuint CreateVertexBufferHandle() const;

/* @section Private variable */
private:
    std::size_t m_dataBytes;
    bool m_isDynamicUsage;
    GLuint m_vertexBufferHandle;
    std::vector<VertexBufferDesc> m_vertexBufferDescs;
};

} /* namespace tgon */