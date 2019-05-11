#include "PrecompiledHeader.h"

#include "Diagnostics/Log.h"
#include "IO/Path.h"
#include "Graphics/Sprite.h"
#include "OpenGL/OpenGLShaderCode.h"

#include "Graphics.h"
#include "Texture.h"
#include "Material.h"
#include "MeshUtility.h"
#include "Camera.h"
#include "View.h"

namespace tgon
{

View::View()
{
    this->PrepareDefaultMaterials();
}

void View::Update()
{
    m_spriteBatches.clear();
    
    for (const auto& sprites : m_spriteLayer)
    {
        for (const auto& sprite : sprites.second)
        {
            if (m_spriteBatches.empty())
            {
                m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect()));
                return;
            }
            
            auto& spriteBatch = m_spriteBatches.back();
            if (spriteBatch.CanBatch(*sprite))
            {
                spriteBatch.Merge(*sprite);
            }
            else
            {
                m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect()));
            }
        }
    }
}

void View::Draw(Graphics& graphics)
{
//#ifndef NDEBUG
//    if (m_cameraList.size() <= 0)
//    {
//        Log(LogLevel::Debug, "You have no camera but trying to draw.\n");
//    }
//#endif
    
    static auto quad = MeshUtility::GetSharedQuad();
    quad->Use();

    this->FlushSpriteBatches(graphics);
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
    
void View::PrepareDefaultMaterials()
{
    m_uiMaterial = std::make_shared<Material>(g_positionUVVert, g_positionUVFrag);
}
    
void View::FlushSpriteBatches(Graphics& graphics)
{
    m_uiMaterial->Use();
    
    for (auto& camera : m_cameraList)
    {
        m_uiMaterial->GetShaderProgram().SetParameterMatrix4fv("g_uWVP", camera->GetViewProjectionMatrix()[0]);
        
        for (auto& spriteBatch : m_spriteBatches)
        {
            spriteBatch.FlushBatch(graphics);
        }
    }
}

} /* namespace tgon */
