#include "PrecompiledHeader.h"

#include <memory>

#include "Scene.h"

namespace tgon
{

std::shared_ptr<Scene> Scene::Create()
{
    Scene scene(StringHash{}, std::shared_ptr<Transform>{});;
    return {};
}

} /* namespace tgon */
