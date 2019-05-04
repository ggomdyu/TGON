#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"
#include "Graphics/Render/Sprite.h"

#include "../LowLevel/Graphics.h"
#include "../LowLevel/Texture.h"

#include "View.h"

namespace tgon
{

void View::Update()
{
    for (const auto& sprites : m_spriteLayer)
    {
        for (const auto& sprite : sprites.second)
        {
            if (m_spriteBatches.empty())
            {
                m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->GetScissorRect()));
                return;
            }
            
            auto& spriteBatch = m_spriteBatches.back();
            if (spriteBatch.CanBatch(*sprite))
            {
                spriteBatch.Merge(*sprite);
            }
            else
            {
                
            }
        }
    }
}

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

//        m_spriteBatchGroup.FlushBatch(graphics, *camera);
    }
}
    
void View::AddSprite(const std::shared_ptr<Sprite>& sprite)
{
    m_spriteLayer[sprite->GetLayer()].push_back(sprite);
}

void View::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
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
