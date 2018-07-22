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
    
//Batch::Batch(const std::shared_ptr<Material>& material) :
//    m_material(material)
//{
//}
//
////Batch::Batch(const MeshRenderer& meshRenderer)
////{
////}
////    
//void Batch::AddMeshRenderer(const MeshRenderer& meshRenderer)
//{
//    m_meshRenderers.push_back(meshRenderer);
//}
//    
//bool Batch::CanBatch(const Material& material) const
//{
//    return m_material->CanBatch(material);
//}
//    
void Batch::Draw(Graphics& graphics)
{
    m_material->Use();
    
    for (auto& meshRenderer : m_meshRenderers)
    {
        m_material->SetWVP(meshRenderer.GetWVP());
        
        auto& mesh = meshRenderer.GetMesh();
        auto& vertexBuffer = mesh->GetVertexBuffer();
        auto& indexBuffer = mesh->GetIndexBuffer();
         
        vertexBuffer->Use();
        indexBuffer->Use();
        
        int32_t primitiveCount = static_cast<int32_t>(indexBuffer->GetDataBytes() / sizeof(unsigned int));
        graphics.DrawPrimitives(PrimitiveType::Triangles, primitiveCount);
    }
}
//
//void BatchGroup::AddMeshRenderer(const MeshRenderer& meshRenderer)
//{
//    for (auto& batch : m_batches)
//    {
//        if (batch.CanBatch(*meshRenderer.GetMaterial()) == true)
//        {
//            batch.AddMeshRenderer(meshRenderer);
//            return;
//        }
//    }
//    
//    m_batches.emplace_back(meshRenderer.GetMaterial(), meshRenderer.GetMesh());
//}
//    
//void BatchGroup::AddBatch(const Batch& batch)
//{
//    m_batches.push_back(batch);
//}
//
void BatchGroup::Draw(Graphics& graphics)
{
    for (auto& batch : m_batches)
    {
        batch.Draw(graphics);
    }
}
    
} /* namespace tgon */
