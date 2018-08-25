#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"

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

void RenderStage::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

RenderStage::CameraList& RenderStage::GetCameraList() noexcept
{
    return m_cameraList;
}

const RenderStage::CameraList& RenderStage::GetCameraList() const noexcept
{
    return m_cameraList;
}
    
bool RenderStage::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& comp)
    {
        return camera == comp;
    });
    if (iter != m_cameraList.end())
    {
        m_cameraList.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

void RenderStage::Draw(Graphics& graphics)
{
#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Log(LogLevel::Debug, "You have no camera but trying to draw.\n");
    }
#endif
    
    for (const auto& camera : m_cameraList)
    {
        m_batchGroup.FlushBatch(graphics, *camera);

        m_spriteBatchGroup.FlushSpriteBatch(graphics, *camera);
    }
}
    
} /* namespace tgon */
