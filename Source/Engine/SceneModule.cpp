#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    if (m_nextScene != nullptr)
    {
        m_currScene = std::move(m_nextScene);
    }
    
    if (m_currScene != nullptr)
    {
        m_currScene->Update();
    }
}

void SceneModule::ChangeScene(const std::shared_ptr<Scene>& scene)
{
    // If there's no scene, then initialize it immediately.
    if (m_currScene == nullptr)
    {
        m_currScene = scene;
        return;
    }

    // Otherwise, the scene will be initialized on next frame.
    m_nextScene = scene;
}

} /* namespace tgon */
