/**
 * @file    Mesh.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <memory>

namespace tgon
{
    
class VertexBuffer;
class IndexBuffer;

class Mesh
{
/* @section Public constructor */
public:
    explicit Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);

/* @section Public method */
public:
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    
    const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const noexcept;
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} /* namespace tgon */
