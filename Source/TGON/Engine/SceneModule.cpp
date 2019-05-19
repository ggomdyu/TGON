#include "PrecompiledHeader.h"

#include "Game/Scene.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    m_currScene->Update();
}

const Scene& SceneModule::GetCurrentScene() const noexcept
{
    return *m_currScene;
}

void SceneModule::ChangeScene(Scene* scene)
{
    m_currScene.reset(scene);
}

Scene& SceneModule::GetCurrentScene() noexcept
{
    return *m_currScene;
}

} /* namespace tgon */
