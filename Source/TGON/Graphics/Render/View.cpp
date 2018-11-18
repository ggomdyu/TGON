#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"

#include "View.h"

namespace tgon
{

void View::Draw(Graphics& graphics)
{
#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Log(LogLevel::Debug, "You have no camera but trying to draw.\n");
    }
#endif
    
    for (const auto& camera : m_cameraList)
    {
        //m_batchGroup.FlushBatch(m_graphics, *camera);

        m_spriteBatchGroup.FlushBatch(graphics, *camera);
    }
}

void View::AddSpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld)
{
    m_spriteBatchGroup.AddSpriteBatch(blendColor, sprite, material, matWorld);
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

} /* namespace tgon */
