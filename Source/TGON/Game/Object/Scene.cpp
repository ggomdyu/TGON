#include "PrecompiledHeader.h"

#include "Scene.h"
#include "GameObject.h"

namespace tgon
{

bool Scene::AddObject(std::shared_ptr<GameObject> object)
{   
    auto ret = m_objects.emplace(object->GetName().GetHashCode(), object);
    return ret.second;
}

bool Scene::RemoveObject(const StringViewHash& objectName)
{
    auto iter = m_objects.find(objectName.GetHashCode());
    if (iter == m_objects.end())
    {
        return false;
    }

    m_objects.erase(iter);
    return true;
}

bool Scene::RemoveObject(GameObject* object)
{
    return this->RemoveObject(StringViewHash(object->GetName().CStr(), object->GetName().Length()));
}

std::shared_ptr<GameObject> Scene::GetObject(const StringViewHash& objectName)
{
    auto iter = m_objects.find(objectName.GetHashCode());
    if (iter == m_objects.end())
    {
        return nullptr;
    }

    return iter->second;
}

std::shared_ptr<const GameObject> Scene::GetObject(const StringViewHash& objectName) const
{
    auto iter = m_objects.find(objectName.GetHashCode());
    if (iter == m_objects.end())
    {
        return nullptr;
    }

    return iter->second;
}

} /* namespace tgon */
