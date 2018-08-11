#include "PrecompiledHeader.h"

#include "../LowLevel/GraphicsType.h"

#include "Batch.h"

namespace tgon
{
    
Batch::Batch(const std::shared_ptr<Material>& material) :
    m_material(material)
{
}

Batch::Batch(const std::shared_ptr<Material>& material, const std::initializer_list<std::shared_ptr<Mesh>>& meshes) :
    m_material(material),
    m_meshes(meshes)
{
}

void Batch::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_meshes.push_back(mesh);
}
    
bool Batch::CanBatch(const std::shared_ptr<Material>& material) const
{
    return m_material->CanBatch(*material);
}
    
void Batch::Draw(Graphics& graphics)
{
    m_material->Use();

    for (auto& mesh : m_meshes)
    {
        auto& vertexBuffer = mesh->GetVertexBuffer();
        auto& indexBuffer = mesh->GetIndexBuffer();

        vertexBuffer->Use();
        indexBuffer->Use();

        int32_t primitiveCount = static_cast<int32_t>(indexBuffer->GetDataBytes() / sizeof(unsigned int));
        graphics.DrawPrimitives(PrimitiveType::Triangles, primitiveCount);
    }
}
    
void BatchGroup::AddBatch(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh)
{
    for (auto& batch : m_batches)
    {
        if (batch.CanBatch(material))
        {
            batch.AddMesh(mesh);
            return;
        }
    }
    
    m_batches.push_back(Batch(material, {mesh}));
}

void BatchGroup::AddBatch(const Batch& batch)
{
    m_batches.push_back(batch);
}

void BatchGroup::FlushBatch(Graphics& graphics)
{
    for (auto& batch : m_batches)
    {
        batch.Draw(graphics);
    }
}
    
} /* namespace tgon */
