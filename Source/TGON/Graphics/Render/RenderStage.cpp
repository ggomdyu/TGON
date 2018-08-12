#include "PrecompiledHeader.h"

#include "RenderStage.h"

namespace tgon
{
    
void RenderStage::AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive)
{
    m_batchGroup.AddBatch(material, drawPrimitive);
}

void RenderStage::AddBatch(const Batch& batch)
{
    m_batchGroup.AddBatch(batch);
}

void RenderStage::AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive)
{
    m_spriteBatchGroup.AddSpriteBatch(material, drawPrimitive);
}

void RenderStage::AddSpriteBatch(const SpriteBatch& spriteBatch)
{
    m_spriteBatchGroup.AddSpriteBatch(spriteBatch);
}

void RenderStage::Draw(Graphics& graphics)
{
    m_batchGroup.FlushBatch(graphics);

    m_spriteBatchGroup.FlushSpriteBatch(graphics);
}
    
} /* namespace tgon */
