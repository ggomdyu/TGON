#include "PrecompiledHeader.h"

#include "../LowLevel/VertexBufferType.h"

#include "MeshUtility.h"
#include "FVF.h"

namespace tgon
{

std::shared_ptr<Mesh> MakeTriangle(std::shared_ptr<Material> material)
{
    // Create a VertexBuffer
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
    auto vertexBuffer = std::make_shared<VertexBuffer>(vertices, false, vertexBufferDescs);

    // Create a IndexBuffer
    unsigned int indices[] = { 0, 1, 2 };
    auto indexBuffer = std::make_shared<IndexBuffer>(indices, false);

    // Create a Mesh
    return std::make_shared<Mesh>(vertexBuffer, indexBuffer, material);
};

std::shared_ptr<Mesh> MakeCube(std::shared_ptr<Material> material)
{
    // Create a VertexBuffer
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
    auto vertexBuffer = std::make_shared<VertexBuffer>(vertices, false, vertexBufferDescs);

    // Create a IndexBuffer
    unsigned int indices[] =
    {
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
    auto indexBuffer = std::make_shared<IndexBuffer>(indices, false);

    // Create a Mesh
    return std::make_shared<Mesh>(vertexBuffer, indexBuffer, material);
};

std::shared_ptr<Mesh> MakeQuad(std::shared_ptr<Material> material)
{
    // Create a VertexBuffer
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
    auto vertexBuffer = std::make_shared<VertexBuffer>(vertices, false, vertexBufferDescs);

    // Create a IndexBuffer
    unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
    auto indexBuffer = std::make_shared<IndexBuffer>(indices, false);

    // Create a Mesh
    return std::make_shared<Mesh>(vertexBuffer, indexBuffer, material);
};

} /* namespace tgon */
