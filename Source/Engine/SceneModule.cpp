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

void SceneManager::Update()
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->Update();
    }
}

void SceneManager::NewScene(NewSceneSetup newSceneSetup)
{
}

void SceneManager::OpenScene(const std::string& path, OpenSceneMode openSceneMode)
{
}

//std::shared_ptr<GameObject> SceneModule::Instantiate()
//{
//}
}
