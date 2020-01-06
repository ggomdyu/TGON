#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
    m_objectMap.emplace(object->GetName(), object);
    m_objectVector.push_back(object);
}

void Scene::AddObject(std::shared_ptr<GameObject>&& object)
{
    m_objectMap.emplace(object->GetName(), object);
    m_objectVector.push_back(std::move(object));
}

std::shared_ptr<GameObject> Scene::FindObject(const StringViewHash& objectName)
{
    auto iter = m_objectMap.find(objectName);
    if (m_objectMap.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}

std::shared_ptr<const GameObject> Scene::FindObject(const StringViewHash& objectName) const
{
    return const_cast<Scene*>(this)->FindObject(objectName);
}

bool Scene::RemoveObject(const StringViewHash& objectName)
{
    auto mapIter = m_objectMap.find(objectName);
    if (mapIter == m_objectMap.end())
    {
        return false;
    }

    m_objectMap.erase(objectName);
    m_objectVector.erase(std::find_if(m_objectVector.begin(), m_objectVector.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    return true;
}

void Scene::RemoveAllObject()
{
    m_objectVector.clear();
    m_objectMap.clear();
}

void Scene::Update()
{
    for (auto& object : m_objectVector)
    {
        object->Update();
    }
}

} /* namespace tgon */
