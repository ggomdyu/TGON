/**
 * @file    Mesh.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <memory>

#include "Math/Matrix4x4.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace tgon
{

class Mesh final
{
/**@section Constructor */
public:
    /**@brief   Initializes with vertex buffer and index buffer. */
    Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);

    /**@brief   Initializes with the r-value reference. */
    Mesh(Mesh&& rhs) = default;
    
/**@section Operator */
public:
    /**@brief   Assigns with the r-value reference. */
    Mesh& operator=(Mesh&& rhs) = default;

/**@section Method */
public:
    void Use();

    /**@brief   Sets the vertex buffer. */
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    
    /**@brief   Sets the index buffer. */
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    
    /**@brief   Gets the vertex buffer. */
    std::shared_ptr<VertexBuffer> GetVertexBuffer() noexcept;
    
    /**@brief   Gets the vertex buffer. */
    std::shared_ptr<const VertexBuffer> GetVertexBuffer() const noexcept;
    
    /**@brief   Gets the index buffer. */
    std::shared_ptr<IndexBuffer> GetIndexBuffer() noexcept;
    
    /**@brief   Gets the index buffer. */
    std::shared_ptr<const IndexBuffer> GetIndexBuffer() const noexcept;

/**@section Variable */
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} /* namespace tgon */
