#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

std::vector<std::shared_ptr<GameObject>> Scene::m_globalObjects;
std::unordered_map<StringHash, std::shared_ptr<GameObject>> Scene::m_globalObjectHashMap;

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
    m_objectHashMap.emplace(object->GetName(), object);
    m_objects.push_back(object);
}

void Scene::AddObject(std::shared_ptr<GameObject>&& object)
{
    m_objectHashMap.emplace(object->GetName(), object);
    m_objects.push_back(std::move(object));
}

void Scene::AddGlobalObject(const std::shared_ptr<GameObject>& object)
{
    m_globalObjectHashMap.emplace(object->GetName(), object);
    m_globalObjects.push_back(object);
}

void Scene::AddGlobalObject(std::shared_ptr<GameObject>&& object)
{
    m_globalObjectHashMap.emplace(object->GetName(), object);
    m_globalObjects.push_back(std::move(object));
}

std::shared_ptr<GameObject> Scene::FindObject(const StringViewHash& objectName)
{
    auto iter = m_objectHashMap.find(objectName);
    if (m_objectHashMap.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}

std::shared_ptr<const GameObject> Scene::FindObject(const StringViewHash& objectName) const
{
    return const_cast<Scene*>(this)->FindObject(objectName);
}

std::shared_ptr<GameObject> Scene::FindGlobalObject(const StringViewHash& objectName)
{
    auto iter = m_globalObjectHashMap.find(objectName);
    if (m_globalObjectHashMap.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}
    
bool Scene::RemoveObject(const StringViewHash& objectName)
{
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    m_objectHashMap.erase(objectName);
    return true;
}

bool Scene::RemoveGlobalObject(const StringViewHash& objectName)
{
    m_globalObjects.erase(std::remove_if(m_globalObjects.begin(), m_globalObjects.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    m_globalObjectHashMap.erase(objectName);
    return true;
}

void Scene::Update()
{
    for (auto& object : m_objects)
    {
        object->Update();
    }

    for (auto& object : m_globalObjects)
    {
        object->Update();
    }
}

} /* namespace tgon */
