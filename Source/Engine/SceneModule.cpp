#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    if (m_currScene != nullptr)
    {
        m_currScene->Update();
    }
}

void SceneModule::ChangeScene(const std::shared_ptr<Scene>& scene)
{
    m_currScene = scene;
}

} /* namespace tgon */
