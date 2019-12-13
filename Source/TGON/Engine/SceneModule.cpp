#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    if (m_nextScene != nullptr)
    {
        m_currScene = std::move(m_nextScene);
        m_currScene->Initialize();
    }
    
    if (m_currScene != nullptr)
    {
        m_currScene->Update();
    }

    for (auto& object : m_globalObjects)
    {
        object->Update();
    }
}

void SceneModule::AddGlobalObject(const std::shared_ptr<GameObject>& object)
{
    m_globalObjectDict.emplace(object->GetName(), object);
    m_globalObjects.push_back(object);
}

void SceneModule::AddGlobalObject(std::shared_ptr<GameObject>&& object)
{
    m_globalObjectDict.emplace(object->GetName(), object);
    m_globalObjects.push_back(std::move(object));
}

std::shared_ptr<GameObject> SceneModule::FindGlobalObject(const StringViewHash& objectName)
{
    auto iter = m_globalObjectDict.find(objectName);
    if (m_globalObjectDict.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}
    
bool SceneModule::RemoveGlobalObject(const StringViewHash& objectName)
{
    m_globalObjects.erase(std::remove_if(m_globalObjects.begin(), m_globalObjects.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return objectName == item->GetName();
    }));
    
    m_globalObjectDict.erase(objectName);
    return true;
}

} /* namespace tgon */
