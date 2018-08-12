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

RenderStage::CameraHandle RenderStage::AddCamera(const Camera& camera)
{
    CameraHandle cameraHandle = m_cameraList.size();

    m_cameraList.push_back(camera);

    return cameraHandle;
}

Camera& RenderStage::GetCamera(CameraHandle cameraHandle)
{
    return m_cameraList[cameraHandle];
}

const Camera& RenderStage::GetCamera(CameraHandle cameraHandle) const
{
    return m_cameraList[cameraHandle];
}

void RenderStage::Draw(Graphics& graphics)
{
    for (const auto& camera : m_cameraList)
    {
        m_batchGroup.FlushBatch(graphics, camera);

        m_spriteBatchGroup.FlushSpriteBatch(graphics, camera);
    }
}
    
} /* namespace tgon */
