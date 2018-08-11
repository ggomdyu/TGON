#include "PrecompiledHeader.h"

#include "GameScene.h"

namespace tgon
{

void GameScene::AddObject(const std::shared_ptr<GameObject>& object)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), object->GetName().GetHashCode(), predicate);

    m_objects.insert(iter, object);
}

GameObject* GameScene::GetObject(const char* objectName)
{
    auto predicate = [&](const std::shared_ptr<GameObject>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_objects.begin(), m_objects.end(), X65599Hash(objectName), predicate);
    if (iter != m_objects.end())
    {
        return (*iter).get();
    }
    else
    {
        return nullptr;
    }
}

const GameObject* GameScene::GetObject(const char* objectName) const
{
    return const_cast<GameScene*>(this)->GetObject(objectName);
}

void GameScene::Update()
{
    for (auto& object : m_objects)
    {
        object->Update();
    }
}

} /* namespace tgon */
