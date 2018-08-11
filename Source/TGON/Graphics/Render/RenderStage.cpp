#include "PrecompiledHeader.h"

#include "RenderStage.h"

namespace tgon
{
    
void RenderStage::AddBatch(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh)
{
    m_batchGroup.AddBatch(material, mesh);
}

void RenderStage::AddBatch(const Batch& batch)
{
    m_batchGroup.AddBatch(batch);
}

void RenderStage::Draw(Graphics& graphics)
{
    m_batchGroup.FlushBatch(graphics);
}
    
} /* namespace tgon */
