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

void Scene::AddGlobalObject(const std::shared_ptr<GameObject>& object)
{
    m_globalObjectDict.emplace(object->GetName(), object);
    m_globalObjects.push_back(object);
}

void Scene::AddGlobalObject(std::shared_ptr<GameObject>&& object)
{
    m_globalObjectDict.emplace(object->GetName(), object);
    m_globalObjects.push_back(std::move(object));
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

std::shared_ptr<GameObject> Scene::FindGlobalObject(const StringViewHash& objectName)
{
    auto iter = m_globalObjectDict.find(objectName);
    if (m_globalObjectDict.end() == iter)
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
    
    m_objectDict.erase(objectName);
    return true;
}

bool Scene::RemoveGlobalObject(const StringViewHash& objectName)
{
    m_globalObjects.erase(std::remove_if(m_globalObjects.begin(), m_globalObjects.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    m_globalObjectDict.erase(objectName);
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
