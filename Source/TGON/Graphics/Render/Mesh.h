/**
 * @filename    Mesh.h
 * @author      ggomdyu
 * @since       01/06/2018
 */

#pragma once
#include "../LowLevelRender/VertexBuffer.h"
#include "../LowLevelRender/IndexBuffer.h"

#include "GraphicsResource.h"
#include "Material.h"

namespace tgon
{

class Mesh :
    public GraphicsResource
{
/* @section Public constructor */
public:
    template <typename _VertexBufferType, typename _IndexBufferType>
    explicit Mesh(const SharedGraphicsContext& context, _VertexBufferType&& vertexBuffer, _IndexBufferType&& indexBuffer);

/* @section Public method */
public:
    VertexBuffer& GetVertexBuffer() noexcept;
    IndexBuffer& GetIndexBuffer() noexcept;

/* @section Protected variable */
protected:
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;
};

template<typename _VertexBufferType, typename _IndexBufferType>
inline Mesh::Mesh(const SharedGraphicsContext& context, _VertexBufferType&& vertexBuffer, _IndexBufferType&& indexBuffer) :
    GraphicsResource(context),
    m_vertexBuffer(std::forward<_VertexBufferType>(vertexBuffer)),
    m_indexBuffer(std::forward<_IndexBufferType>(indexBuffer))
{
}

inline VertexBuffer& Mesh::GetVertexBuffer() noexcept
{
    return m_vertexBuffer;
}

inline IndexBuffer& Mesh::GetIndexBuffer() noexcept
{
    return m_indexBuffer;
}

} /* namespace tgon */