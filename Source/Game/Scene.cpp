#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

Scene::Scene() :
    GameObject(StringHash{}, std::make_shared<Transform>())
{
}

std::unique_ptr<Scene> Scene::Create()
{
    return std::unique_ptr<Scene>(new Scene());
}

} /* namespace tgon */
