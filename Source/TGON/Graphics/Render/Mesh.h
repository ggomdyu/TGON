/**
 * @file    Mesh.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <memory>

#include "Core/Math/Matrix4x4.h"

#include "../LowLevel/VertexBuffer.h"
#include "../LowLevel/IndexBuffer.h"

namespace tgon
{

class Mesh final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the mesh with vertex buffer and index buffer. */
    Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
    
/* @section Public method */
public:
    /* @brief   Sets the vertex buffer. */
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    
    /* @brief   Sets the index buffer. */
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    
    /* @brief   Gets the vertex buffer. */
    const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const noexcept;
    
    /* @brief   Gets the index buffer. */
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} /* namespace tgon */
