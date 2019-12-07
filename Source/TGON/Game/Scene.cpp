#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{   
    m_objectDict.emplace(object->GetName(), object);
    m_objects.push_back(object);
}

void Scene::AddObject(std::shared_ptr<GameObject>&& object)
{
    m_objectDict.emplace(object->GetName(), object);
    m_objects.push_back(std::move(object));
}

std::shared_ptr<GameObject> Scene::FindObject(const StringViewHash& objectName)
{
    auto iter = m_objectDict.find(objectName);
    if (m_objectDict.end() == iter)
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
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    m_objectDict.erase(objectName);
    return true;
}

void Scene::Update()
{
    for (auto& object : m_objects)
    {
        object->Update();
    }
}

} /* namespace tgon */
