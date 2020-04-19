#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tg
{

void Scene::Update()
{
    for (auto& gameObject : m_gameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Update();
        }
    }
}

void SceneModule::Update()
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->Update();
    }
}

void SceneModule::NewScene(NewSceneSetup newSceneSetup)
{
}

void SceneModule::OpenScene(const std::string& path, OpenSceneMode openSceneMode)
{
}

std::shared_ptr<GameObject> SceneModule::Instantiate()
{
}
}
