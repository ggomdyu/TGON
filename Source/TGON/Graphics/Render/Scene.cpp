#include "PrecompiledHeader.h"

#include "Scene.h"

namespace tgon
{
//
//bool Scene::AddObject(const std::shared_ptr<GameObject>& object)
//{   
//    auto ret = m_objects.emplace(object->GetName().GetHashCode(), object);
//    return ret.second;
//}
//
//bool Scene::RemoveObject(const StringViewHash& objectName)
//{
//    auto iter = m_objects.find(objectName.GetHashCode());
//    if (iter == m_objects.end())
//    {
//        return false;
//    }
//
//    m_objects.erase(iter);
//    return true;
//}
//
//bool Scene::RemoveObject(const std::shared_ptr<GameObject>& object)
//{
//    return this->RemoveObject(StringViewHash(object->GetName().CStr(), object->GetName().Length()));
//}
//
//GameObject* Scene::GetObject(const StringViewHash& objectName) noexcept
//{
//    auto iter = m_objects.find(objectName.GetHashCode());
//    if (iter == m_objects.end())
//    {
//        return nullptr;
//    }
//    
//    return iter->second.get();
//}
//    
//const GameObject* Scene::GetObject(const StringViewHash& objectName) const noexcept
//{
//    return const_cast<Scene*>(this)->GetObject(objectName);
//}
//
//void Scene::Update(float deltaTime)
//{
//    for (auto& object : m_objects)
//    {
//        object.second->Update();
//    }
//}
//    
//void Scene::Draw()
//{
//}
    
} /* namespace tgon */
