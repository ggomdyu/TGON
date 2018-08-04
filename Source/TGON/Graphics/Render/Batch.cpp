#include "PrecompiledHeader.h"

#include "../LowLevel/Graphics.h"
#include "../LowLevel/GraphicsType.h"
#include "../LowLevel/VertexBuffer.h"
#include "../LowLevel/IndexBuffer.h"

#include "Material.h"
#include "Mesh.h"
#include "Batch.h"

namespace tgon
{
    
Batch::Batch(const std::shared_ptr<Material>& material) :
    m_material(material)
{
}

void Batch::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_meshes.push_back(mesh);
}
    
bool Batch::CanBatch(const Material& material) const
{
    return m_material->CanBatch(material);
}
    
void Batch::Draw(Graphics& graphics)
{
    m_material->Use();

    for (auto& mesh : m_meshes)
    {
//        m_material->SetWVP(mesh->GetWVP());

        auto& vertexBuffer = mesh->GetVertexBuffer();
        auto& indexBuffer = mesh->GetIndexBuffer();

        vertexBuffer->Use();
        indexBuffer->Use();

        int32_t primitiveCount = static_cast<int32_t>(indexBuffer->GetDataBytes() / sizeof(unsigned int));
        graphics.DrawPrimitives(PrimitiveType::Triangles, primitiveCount);
    }
}

void BatchGroup::AddBatch(const Batch& batch)
{
    m_batches.push_back(batch);
}

void BatchGroup::Draw(Graphics& graphics)
{
    for (auto& batch : m_batches)
    {
        batch.Draw(graphics);
    }
}
    
} /* namespace tgon */
