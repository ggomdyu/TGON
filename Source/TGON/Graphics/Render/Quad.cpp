#include "PrecompiledHeader.pch"

#include "Quad.h"
#include "FVF.h"

namespace tgon
{

Quad::Quad(const SharedGraphicsContext& context) :
    Mesh(context, [&]()
    {
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)},
        };
        
        std::initializer_list<VertexBufferDesc> vertexBufferDescs =
        {
            VertexBufferDesc(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferDesc(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };

        VertexBuffer vertexBuffer(vertices, false, vertexBufferDescs);
        VertexBuffer vertexBuffer2(vertices, false, vertexBufferDescs);
        vertexBuffer2 = std::move(vertexBuffer);
        return vertexBuffer;
    } (), [&]()
    {
        unsigned int indices[] = {0, 1, 2, 0, 2, 3};

        IndexBuffer indexBuffer(indices, false);
        return indexBuffer;
    } ())
{
}

} /* namespace tgon */