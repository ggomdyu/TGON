/**
 * @file    Mesh.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "../LowLevel/VertexBuffer.h"
#include "../LowLevel/IndexBuffer.h"

#include "Material.h"

namespace tgon
{

class Mesh
{
/* @section Public constructor */
public:
    explicit Mesh(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Material> material);

/* @section Public method */
public:
    void SetVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
    void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);
    void SetMaterial(std::shared_ptr<Material> material);
    
    std::shared_ptr<VertexBuffer> GetVertexBuffer() noexcept;
    std::shared_ptr<IndexBuffer> GetIndexBuffer() noexcept;
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const VertexBuffer> GetVertexBuffer() const noexcept;
    std::shared_ptr<const IndexBuffer> GetIndexBuffer() const noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    std::shared_ptr<Material> m_material;
};

} /* namespace tgon */
