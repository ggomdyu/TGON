#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{

std::vector<std::shared_ptr<GameObject>> Scene::m_globalObjects;
std::unordered_map<int32_t, int32_t> Scene::m_globalObjectNameHashMap;

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
    m_objectNameHashMap.emplace(object->GetName().GetHashCode(), m_objects.size());
    m_objects.push_back(object);
}

void Scene::AddGlobalObject(const std::shared_ptr<GameObject>& object)
{
    m_globalObjectNameHashMap.emplace(object->GetName().GetHashCode(), m_objects.size());
    m_globalObjects.push_back(object);
}

std::shared_ptr<GameObject> Scene::FindObject(const StringViewHash& objectName)
{
    auto iter = m_objectNameHashMap.find(objectName.GetHashCode());
    if (m_objectNameHashMap.end() == iter)
    {
        return nullptr;
    }

    return m_objects[iter->second];
}

const std::shared_ptr<GameObject> Scene::FindObject(const StringViewHash& objectName) const
{
    return const_cast<Scene*>(this)->FindObject(objectName);
}

std::shared_ptr<GameObject> Scene::FindGlobalObject(const StringViewHash& objectName)
{
    auto iter = m_globalObjectNameHashMap.find(objectName.GetHashCode());
    if (m_globalObjectNameHashMap.end() == iter)
    {
        return nullptr;
    }

    return m_globalObjects[iter->second];
}

std::shared_ptr<const GameObject> Scene::FindGlobalObject(const StringViewHash& objectName) const
{
    return const_cast<Scene*>(this)->FindGlobalObject(objectName);
}
    
bool Scene::RemoveObject(const StringViewHash& objectName)
{
    auto objectNameHashMapIter = m_objectNameHashMap.find(objectName.GetHashCode());
    if (m_objectNameHashMap.end() == objectNameHashMapIter)
    {
        return false;
    }

    m_objectNameHashMap.erase(objectNameHashMapIter);
    m_objects.erase(m_objects.begin() + objectNameHashMapIter->second);

    return true;
}

bool Scene::RemoveGlobalObject(const StringViewHash& objectName)
{
    auto objectNameHashMapIter = m_globalObjectNameHashMap.find(objectName.GetHashCode());
    if (m_globalObjectNameHashMap.end() == objectNameHashMapIter)
    {
        return false;
    }

    m_globalObjectNameHashMap.erase(objectNameHashMapIter);
    m_globalObjects.erase(m_globalObjects.begin() + objectNameHashMapIter->second);

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

}
