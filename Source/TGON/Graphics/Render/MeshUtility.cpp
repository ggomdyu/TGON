#include "PrecompiledHeader.pch"

#include "MeshUtility.h"
#include "FVF.h"

namespace tgon
{

Triangle::Triangle(const SharedGraphicsContext& context) :
    Mesh(context, [&]()
    {
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(0.0f, 1.0f, 0.0f), Vector2(0.5f, 1.0f)},
            V3F_T2F{Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)},
        };
        
        std::initializer_list<VertexBufferDesc> vertexBufferDescs =
        {
            VertexBufferDesc(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferDesc(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };

        return VertexBuffer(vertices, false, vertexBufferDescs);
    } (), [&]()
    {
        unsigned int indices[] = {0, 1, 2};

        IndexBuffer indexBuffer(indices, false);
        return indexBuffer;
    } ())
{
}

Cube::Cube(const SharedGraphicsContext& context) :
    Mesh(context, [&]()
    {
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f)},
            V3F_T2F{Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 0.0f)},
        };
        
        std::initializer_list<VertexBufferDesc> vertexBufferDescs =
        {
            VertexBufferDesc(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferDesc(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };

        return VertexBuffer(vertices, false, vertexBufferDescs);
    } (), [&]()
    {
        unsigned int indices[] = {
            // Front face
            0, 1, 2,
            0, 2, 3,
            
            // Right face
            3, 2, 6,
            3, 6, 7,
            
            // Back face
            7, 6, 5,
            7, 5, 4,
            
            // Left face
            4, 5, 1,
            4, 1, 0,
            
            // Up face
            1, 5, 6,
            1, 6, 2,
            
            // Down face
            0, 4, 7,
            0, 7, 3
        };

        IndexBuffer indexBuffer(indices, false);
        return indexBuffer;
    } ())
{
}

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

        return VertexBuffer(vertices, false, vertexBufferDescs);
    } (), [&]()
    {
        unsigned int indices[] = {0, 1, 2, 0, 2, 3};

        IndexBuffer indexBuffer(indices, false);
        return indexBuffer;
    } ())
{
}

} /* namespace tgon */