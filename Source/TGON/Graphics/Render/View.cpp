#include "PrecompiledHeader.h"

#include "View.h"

namespace tgon
{
    
//void View::AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive)
//{
//    m_batchGroup.AddBatch(material, drawPrimitive);
//}
//
//void View::AddBatch(const Batch& batch)
//{
//    m_batchGroup.AddBatch(batch);
//}

//void View::AddSpriteBatch(const std::shared_ptr<TextureMaterial>& material, const SpriteBatch::DrawPrimitive& drawPrimitive)
//{
//    m_spriteBatchGroup.AddSpriteBatch(material, drawPrimitive);
//}
//
//void View::AddSpriteBatch(const SpriteBatch& spriteBatch)
//{
//    m_spriteBatchGroup.AddSpriteBatch(spriteBatch);
//}

View::View(const Window& displayWindow, const VideoMode& videoMode) :
    m_graphics(displayWindow, videoMode)
{
}

void View::AddSprite(const Sprite& sprite)
{
    m_spriteBatchGroup.AddSpriteBatch(SpriteBatch(sprite.GetTexture(), SpriteBatch::DrawPrimitive()));
}

void View::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

std::vector<std::shared_ptr<Camera>>& View::GetCameraList() noexcept
{
    return m_cameraList;
}

const std::vector<std::shared_ptr<Camera>>& View::GetCameraList() const noexcept
{
    return m_cameraList;
}
    
bool View::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& comp)
    {
        return comp == camera;
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

void View::Draw()
{
}

void View::Draw()
{
#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Log(LogLevel::Debug, "You have no camera but trying to draw.\n");
    }
#endif
    
    for (const auto& camera : m_cameraList)
    {
        m_batchGroup.FlushBatch(m_graphics, *camera);

        m_spriteBatchGroup.FlushSpriteBatch(m_graphics, *camera);
    }
}
    
} /* namespace tgon */
