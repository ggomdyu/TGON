#include "PrecompiledHeader.h"

#include "MeshUtility.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferType.h"
#include "FVF.h"
#include "Mesh.h"

namespace tgon
{

std::shared_ptr<Mesh> GetSharedTriangle()
{
    static std::shared_ptr<Mesh> sharedMesh = []()
    {
        // Create a VertexBuffer
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(0.0f, 1.0f, 0.0f), Vector2(0.5f, 1.0f)},
            V3F_T2F{Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)},
        };
        std::initializer_list<VertexBufferLayoutDescriptor> vertexBufferLayoutDescs =
        {
            VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };
        auto vertexBuffer = std::make_shared<VertexBuffer>(vertexBufferLayoutDescs);
        vertexBuffer->SetData(vertices, false);

        // Create an IndexBuffer
        unsigned int indices[] = { 0, 1, 2 };
        auto indexBuffer = std::make_shared<IndexBuffer>();
        indexBuffer->SetData(indices, false);

        // Create a Mesh
        return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
    } ();
    
    return sharedMesh;
};

std::shared_ptr<Mesh> GetSharedCube()
{
    static std::shared_ptr<Mesh> sharedMesh = []()
    {
        // Create a VertexBuffer
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f)},
            V3F_T2F{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f)},
        };
        std::initializer_list<VertexBufferLayoutDescriptor> vertexBufferLayoutDescs =
        {
            VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };
        auto vertexBuffer = std::make_shared<VertexBuffer>(vertexBufferLayoutDescs);
        vertexBuffer->SetData(vertices, false);
        
        // Create an IndexBuffer
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
        auto indexBuffer = std::make_shared<IndexBuffer>();
        indexBuffer->SetData(indices, false);
        
        // Create a Mesh
        return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
    } ();
    
    return sharedMesh;
};

std::shared_ptr<Mesh> GetSharedQuad()
{
    static std::shared_ptr<Mesh> sharedMesh = []()
    {
        // Create a VertexBuffer
        V3F_T2F vertices[] =
        {
            V3F_T2F{Vector3(-0.5f, -0.5f, 0.0f), Vector2(0.0f, 0.0f)},
            V3F_T2F{Vector3(-0.5f, 0.5f, 0.0f), Vector2(0.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, 0.5f, 0.0f), Vector2(1.0f, 1.0f)},
            V3F_T2F{Vector3(0.5f, -0.5f, 0.0f), Vector2(1.0f, 0.0f)},
        };
        std::initializer_list<VertexBufferLayoutDescriptor> vertexBufferLayoutDescs =
        {
            VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
            VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
        };
        auto vertexBuffer = std::make_shared<VertexBuffer>(vertexBufferLayoutDescs);
        vertexBuffer->SetData(vertices, false);
        
        // Create an IndexBuffer
        unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
        auto indexBuffer = std::make_shared<IndexBuffer>();
        indexBuffer->SetData(indices, false);
        
        // Create a Mesh
        return std::make_shared<Mesh>(vertexBuffer, indexBuffer);
    } ();
    
    return sharedMesh;
};

} /* namespace tgon */
