#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

Scene::Scene() :
    GameObject(StringHash{}, std::make_shared<Transform>())
{
}

std::shared_ptr<Scene> Scene::Create()
{
    std::shared_ptr<Scene> scene(new Scene());
    
    if (scene->m_transform != nullptr)
    {
        scene->m_transform->SetGameObject(scene);
    }
    
    scene->Initialize();

    return scene;
}

} /* namespace tgon */
