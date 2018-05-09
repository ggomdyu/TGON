/**
 * @filename    Mesh.h
 * @author      ggomdyu
 * @since       01/06/2018
 */

#pragma once
#include "../LowLevelRender/VertexBuffer.h"
#include "../LowLevelRender/IndexBuffer.h"

#include "Material.h"

namespace tgon
{

class Mesh
{
/* @section Public constructor */
public:
    explicit Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<Material>& material);

/* @section Public method */
public:
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    void SetMaterial(const std::shared_ptr<Material>& material);
    const std::shared_ptr<VertexBuffer>& GetVertexBuffer() noexcept;
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() noexcept;
    const std::shared_ptr<Material>& GetMaterial() noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    std::shared_ptr<Material> m_material;
};

} /* namespace tgon */